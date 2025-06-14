#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include <random>
#include "symbol_table.hpp"
#include "reactant_store.hpp"

#ifndef SP_EXAM_VESSEL_HPP
#define SP_EXAM_VESSEL_HPP

struct Environment{
    constexpr static const std::string Name = "Env";
};

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

    Reaction(const PartialReaction& p, const Term& rhs) : delay{p.delay} {
        auto lhs = p.Lhs.GetAgents();
        inputs.insert(inputs.end(), lhs.begin(), lhs.end());
        auto rhsAgents = rhs.GetAgents();
        outputs.insert(outputs.end(), rhsAgents.begin(), rhsAgents.end());
    }
};

struct Vessel {
    // Requirement 3. Implement a generic symbol reactants to store and lookup objects of user-defined key and value types.
    // Demonstrate the usage of the symbol reactants with the reactants (names and initial counts).
    // --- The reactans_store is a specialization of the symbol_table.
    reactant_store<std::string, unsigned> reactants{};

    std::string vesselName;
    std::unordered_map<unsigned, Reaction> reactions{};
    unsigned reactionId = 0;


    explicit Vessel(std::string name){
        vesselName = std::move(name);
    }

    static Environment environment(){
        return Environment{};
    }

    std::shared_ptr<Agent> add(const std::string& agentName, unsigned initialAmount){
        auto success = reactants.store(agentName, initialAmount);
        if (!success){
            throw std::invalid_argument("The following key already exists: " + agentName);
        }
        return std::make_shared<Agent>(agentName);
    }

    void add(const Reaction& r){
        reactions.try_emplace(reactionId, r);
        reactionId++;
    }
};

// Requirement: 1. The library should overload operators to support the reaction rule typesetting directly in C++ code.

inline Term operator+(const std::shared_ptr<Agent>& lhs, const std::shared_ptr<Agent>& rhs) {
    return {lhs, rhs};
}

inline std::shared_ptr<Term> operator+(const Environment& env) {
    return std::make_shared<Term>(env);
}

inline PartialReaction operator>>(const std::shared_ptr<Agent>& lhs, const double delay) {
    return {Term(lhs), delay};
}

inline PartialReaction operator>>(const Term& lhs, const double delay) {
    return {lhs, delay};
}

inline Reaction operator>>=(const PartialReaction& lhs, const Term& rhs) {
    return {lhs, rhs};
}

inline Reaction operator>>=(const PartialReaction& lhs, const std::shared_ptr<Agent>& rhs) {
    return {lhs, Term(rhs)};
}

inline Reaction operator>>=(const PartialReaction& lhs, Environment rhs) {
    return {lhs, Term(rhs)};
}

#endif //SP_EXAM_VESSEL_HPP
