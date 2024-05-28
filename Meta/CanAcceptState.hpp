//
// Created by Henri on 28/05/2024.
//

#ifndef SP_EXAM_CANACCEPTSTATE_HPP
#define SP_EXAM_CANACCEPTSTATE_HPP

#include <unordered_map>
#include <string>

#endif //SP_EXAM_CANACCEPTSTATE_HPP

template <typename T>
concept CanAcceptState = requires(T&& d, std::unordered_map<std::string, unsigned>& s, const double t) {
{
    d.accept(s, t) };
};