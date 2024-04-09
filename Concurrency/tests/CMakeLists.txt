add_executable(stringsort_test stringsort_test.cpp)
target_link_libraries(stringsort_test PRIVATE stringsort doctest::doctest_with_main)
add_test(NAME stringsort_test COMMAND stringsort_test)

add_executable(stringsort0_bm stringsort0_bm.cpp)
target_link_libraries(stringsort0_bm PRIVATE stringsort benchmark::benchmark_main)
add_test(NAME stringsort0_bm COMMAND stringsort0_bm)

add_executable(stringsort1_bm stringsort1_bm.cpp)
target_link_libraries(stringsort1_bm PRIVATE stringsort benchmark::benchmark_main)
add_test(NAME stringsort1_bm COMMAND stringsort1_bm)

add_executable(stringsort2_bm stringsort2_bm.cpp)
target_link_libraries(stringsort2_bm PRIVATE stringsort benchmark::benchmark_main)
add_test(NAME stringsort2_bm COMMAND stringsort2_bm)

if(OPENMP_FOUND AND HAVE_GNU_PARALLEL)
    add_executable(stringsort3_bm stringsort3_bm.cpp)
    target_link_libraries(stringsort3_bm PRIVATE stringsort OpenMP::OpenMP_CXX benchmark::benchmark_main)
    add_test(NAME stringsort3_bm COMMAND stringsort3_bm)
endif()

if(TBB_FOUND)
    add_executable(stringsort4_bm stringsort4_bm.cpp)
    target_link_libraries(stringsort4_bm PRIVATE stringsort TBB::tbb benchmark::benchmark_main)
    add_test(NAME stringsort4_bm COMMAND stringsort4_bm)
endif()

add_executable(mtqueue_bm mtqueue_bm.cpp)
target_link_libraries(mtqueue_bm PRIVATE Threads::Threads benchmark::benchmark_main)
add_test(NAME mtqueue_bm COMMAND mtqueue_bm)
