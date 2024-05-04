//
// Created by Henri on 11/04/2024.
//
#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>


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

struct Vessel {
    std::string vesselName;
    std::vector<Agent> agents{};
    std::vector<unsigned> moleculeAmount{};


    explicit Vessel(std::string name){
        vesselName = std::move(name);
    }

    static Environment environment(){
        return Environment{};
    }

    Expr add(const std::string& agentName, unsigned initialAmount){
        auto agent = Agent(agentName);
        agents.push_back(agent);
        moleculeAmount.push_back(initialAmount);
        return Expr(std::make_shared<Agent>(agent));
    }
};

inline Expr operator+(const Expr expr1, const Expr expr2) {
    return Expr(std::make_shared<Term>(Term(expr1.var, expr2.var)));
}