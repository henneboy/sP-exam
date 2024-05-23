#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include <random>
#include "symbol_table.hpp"
#include "reactant-store.hpp"

struct Environment{};

struct Agent{
    std::string Name;
    explicit Agent(std::string name) : Name{std::move(name)}{}
};

struct Term{
    std::optional<std::shared_ptr<Term>> LhsTerm;
    std::optional<std::shared_ptr<Agent>> LhsAgent;
    std::optional<std::shared_ptr<Agent>> Rhs;

    Term(const std::shared_ptr<Term>& lhs, const std::shared_ptr<Agent>& rhs) : LhsTerm(lhs), Rhs(rhs) {}

    Term(const std::shared_ptr<Agent>& lhs, const std::shared_ptr<Agent>& rhs) : LhsAgent(lhs), Rhs(rhs){}

    explicit Term(const std::shared_ptr<Agent>& lhs) : LhsAgent(lhs){}

    explicit Term(Environment _){}

    [[nodiscard]] std::vector<std::string> GetAgents() const{
        std::vector<std::string> agents{};
        if (LhsTerm.has_value()){
            auto temp = LhsTerm.value()->GetAgents();
            agents.insert(agents.end(), temp.begin(), temp.end());
        }
        if (LhsAgent.has_value()){
            agents.push_back(LhsAgent.value()->Name);
        }
        if (Rhs.has_value()){
            agents.push_back(Rhs.value()->Name);
        }
        return agents;
    }
};

struct PartialReaction{
    Term Lhs;
    double delay;
    PartialReaction(Term  lhs, double d) : Lhs{std::move(lhs)}, delay{d}{}
};

struct Reaction{
    std::vector<std::string> inputs{};
    std::vector<std::string> outputs{};
    double delay;

    Reaction(const PartialReaction& p, const Term& rhs){
        auto lhs = p.Lhs.GetAgents();
        inputs.insert(inputs.end(), lhs.begin(), lhs.end());
        delay = p.delay;
        auto rhsAgents = rhs.GetAgents();
        inputs.insert(inputs.end(), rhsAgents.begin(), rhsAgents.end());

    }
};

struct Vessel {
    std::string vesselName;
    reactant_store<std::string, unsigned> table{};
    std::unordered_map<unsigned, Reaction> reactions{};
    unsigned reactionId = 0;
    std::random_device rd;
    std::mt19937 gen(1);

    explicit Vessel(std::string name){
        vesselName = std::move(name);
    }

    static Environment environment(){
        return Environment{};
    }

    std::shared_ptr<Agent> add(const std::string& agentName, unsigned initialAmount){
        auto success = table.Add(agentName, initialAmount);
        if (!success){
            throw std::invalid_argument("The following key already exists: " + agentName);
        }
        return std::make_shared<Agent>(agentName);
    }

    void add(const Reaction& r){
        reactions.emplace(reactionId++, r);
    }
};

struct Simulator{
    Simulator(int seed, Vessel& v) : gen(seed), vessel(v) {}
    std::mt19937 gen;
    Vessel& vessel;
    void simulate(double duration){
        double t = 0;
        while (t < duration){
            auto currentReaction = vessel.reactions.find(nextReaction())->second;
            performReaction(currentReaction);
            vessel.table.getState();
        }
    }

    void performReaction(const Reaction& r){
        for (auto& input: r.inputs) {
            vessel.table.decrement(input);
        }
        for (auto& output: r.outputs) {
            vessel.table.increment(output);
        }
    }

    unsigned nextReaction(){
        unsigned nextReaction = 0;
        double shortestDelay = -1;
        for (const auto& reaction: vessel.reactions) {
            double productOfInputs = 1;
            bool inputExists = false;
            for (const auto& input: reaction.second.inputs){
                auto inputLevel = vessel.table.Lookup(input);
                if (!inputLevel.has_value()){
                    throw std::invalid_argument("Table lookup failed for:" + input);
                }
                productOfInputs *= inputLevel.value();
                inputExists = true;
            }
            if (!inputExists){
                continue;
            }
            std::exponential_distribution<> d(productOfInputs * reaction.second.delay);
            double delay = d(gen);
            if (delay < shortestDelay){
                shortestDelay = delay;
                nextReaction = reaction.first;
            }
        }
    }
};


inline Term operator+(const std::shared_ptr<Agent>& lhs, const std::shared_ptr<Agent>& rhs) {
    return {lhs, rhs};
}

inline std::shared_ptr<Term> operator+(const Environment& env) {
    return std::make_shared<Term>(Term(env));
}

inline PartialReaction operator>>(const std::shared_ptr<Agent>& lhs, const double delay) {
    return PartialReaction{Term(lhs), delay};
}

inline PartialReaction operator>>(const Term& lhs, const double delay) {
    return {lhs, delay};
}

inline Reaction operator>>=(const PartialReaction& lhs, const Term& rhs) {
    return Reaction{lhs, rhs};
}

inline Reaction operator>>=(const PartialReaction& lhs, const std::shared_ptr<Agent>& rhs) {
    return Reaction{lhs, Term(rhs)};
}
