#include "test_as5600.h"

#include "test_simple_foc2.h"
void setup() {
    setup_foc2();
}
void loop() {
    loop_foc2();
}

// #include "test_simple_foc.h"
// TestSimpleFoc test_case = TestSimpleFoc();
// void setup() {
//     test_case.Init();
// }
// void loop() {
//     test_case.Update();
// }