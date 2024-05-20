#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include "symbol_table.hpp"

struct Var{};

struct Expr{
    std::shared_ptr<Var> var;
};

struct Environment : Var{};

struct Agent : Var{
    std::string Name;
    explicit Agent(std::string name){
        Name = std::move(name);
    }
};

struct Term : Var{
    std::shared_ptr<Var> Lhs;
    std::shared_ptr<Var> Rhs;
    Term(const std::shared_ptr<Var>& lhs, const std::shared_ptr<Var>& rhs){
        Lhs = lhs;
        Rhs = rhs;
    }
};

struct PartialReaction{
    PartialReaction(const std::shared_ptr<Var>& lhs, double d){
        Lhs = lhs;
        delay = d;
    }
    std::shared_ptr<Var> Lhs;
    double delay;
};

struct Reaction{
    std::shared_ptr<Var> Lhs;
    double delay;
    std::shared_ptr<Var> Rhs;
    Reaction(const PartialReaction& p, const Expr& rhs){
        Lhs = p.Lhs;
        delay = p.delay;
        Rhs = rhs.var;
    }
};

struct Vessel {
    std::string vesselName;
    symbol_table<std::string, unsigned> table{};
    std::vector<Reaction> reactions{};

    explicit Vessel(std::string name){
        vesselName = std::move(name);
    }

    static Expr environment(){
        return Expr(std::make_shared<Var>(Environment{}));
    }

    Expr add(const std::string& agentName, unsigned initialAmount){
        auto success = table.Add(agentName, initialAmount);
        if (!success){
            throw std::invalid_argument("The following key already exists: " + agentName);
        }
        return Expr(std::make_shared<Agent>(agentName));
    }

    void add(const Reaction& r){
        reactions.push_back(r);
    }

    void simulate(double duration){
        double t = 0;
        std::vector<double> delays(reactions.size());
        while (t < duration){
            delays = calcDelays();
        }
    }

    std::vector<double> calcDelays(){
        std::vector<double> delays(reactions.size());
        for (auto reaction: reactions) {
            // implement calculating delays
        }
    }
};

inline Expr operator+(const Expr& expr1, const Expr& expr2) {
    return {std::make_shared<Term>(Term(expr1.var, expr2.var))};
}

inline PartialReaction operator>>(const Expr& lhs, const double delay) {
    return {lhs.var, delay};
}

inline Reaction operator>>=(const PartialReaction& lhs, const Expr& rhs) {
    return {lhs, rhs};
}
