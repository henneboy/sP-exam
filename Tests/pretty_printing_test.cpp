//
// Created by Henrik on 15-06-2024.
//
#include "doctest/doctest.h"
#include "../Examples/build_circadian_rhythm.h++"
#include "../pretty_printing.h++"
#include <sstream>

TEST_CASE("testing pretty printing of reaction rules")
{
    auto circadianVessel = circadian_rhythm();
    std::stringstream ss;
    ss << circadianVessel;
    CHECK(ss.str() == "Circadian Rhythm\n"
                      "MR--0.5->Env\n"
                      "MA--10->Env\n"
                      "R--0.2->Env\n"
                      "A+DA--1->D_A\n"
                      "D_A--50->DA+A\n"
                      "A+DR--1->D_R\n"
                      "D_R--100->DR+A\n"
                      "D_A--500->MA+D_A\n"
                      "DA--50->MA+DA\n"
                      "D_R--50->MR+D_R\n"
                      "DR--0.01->MR+DR\n"
                      "MA--50->MA+A\n"
                      "MR--5->MR+R\n"
                      "A+R--2->C\n"
                      "C--1->R\n"
                      "A--1->Env\n");
}