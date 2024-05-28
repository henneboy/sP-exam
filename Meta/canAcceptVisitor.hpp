//
// Created by Henri on 28/05/2024.
//

#ifndef SP_EXAM_CANACCEPTVISITOR_HPP
#define SP_EXAM_CANACCEPTVISITOR_HPP

template <typename Entity, typename Visitor>
concept CanAcceptVisitor = requires(Entity&& d, Visitor&& v) { // given an instance c of type T&&
{
    d.accept(v) }; // must be able to accept v
};


#endif //SP_EXAM_CANACCEPTVISITOR_HPP
