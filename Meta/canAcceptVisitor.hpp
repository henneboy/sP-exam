//
// Created by Henri on 28/05/2024.
//

#ifndef SP_EXAM_CANACCEPTVISITOR_HPP
#define SP_EXAM_CANACCEPTVISITOR_HPP

template <typename Data, typename Visitor>
concept CanAcceptVisitor = requires(Data&& d, Visitor&& v) {
        v.plot(d);
};

#endif //SP_EXAM_CANACCEPTVISITOR_HPP
