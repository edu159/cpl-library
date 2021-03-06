#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>

#include "cpl.h"
#include "CPL_field.h"
#include "CPL_force.h"
#include "CPL_ndArray.h"

// The fixture for testing class Foo.
class CPL_interp_Test : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CPL_interp_Test() {
    // You can do set-up work for each test here.
  }

  virtual ~CPL_interp_Test() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

#define trplefor(Ni,Nj,Nz) for (int i = 0; i<Ni; ++i){ \
                           for (int j = 0; j<Nj; ++j){ \
                           for (int k = 0; k<Nz; ++k)


//Test for CPL::ndArray - setup and array size 
TEST_F(CPL_interp_Test, test_celltonode) {
    int nd = 3;
    int icell = 3;
    int jcell = 3;
    int kcell = 3;

    CPL::ndArray<double> buf;
    int shape[4] = {nd, icell, jcell, kcell};
    buf.resize (4, shape);

    //Test define
    int n = 0;
    CPL::CPLField field(buf);
    //Slabs in x
    for (int j = 0; j < jcell; j++ ){
    for (int k = 0; k < kcell; k++ ){
        buf(n,0,j,k) = -0.5;
        buf(n,1,j,k) = 0.5;
        buf(n,2,j,k) = 1.5;
    }}
    CPL::ndArray<double> nodesx = field.celltonode(buf, n, 0, 0, 0);
    trplefor(icell-1,jcell-1,kcell-1){
        //std::cout << "nodex = " << i << " " << j << " " << k << " " 
        //                        << nodesx(n,i,j,k) << "\n"; 
        ASSERT_DOUBLE_EQ(nodesx(n,i,j,k), float(i));
    }}}

    //Slabs in y
    for (int i = 0; i < 3; i++ ){
    for (int k = 0; k < 3; k++ ){
        buf(n,i,0,k) = -0.5;
        buf(n,i,1,k) = 0.5;
        buf(n,i,2,k) = 1.5;
    }}
    CPL::ndArray<double> nodesy = field.celltonode(buf, n, 0, 0, 0);
    trplefor(icell-1,jcell-1,kcell-1){
        //std::cout << "nodey = " << i << " " << j << " " << k << " " 
        //                        << nodesy(n,i,j,k) << "\n"; 
        ASSERT_DOUBLE_EQ(nodesy(n,i,j,k), float(j));

    }}}

    //Slabs in z
    for (int i = 0; i < 3; i++ ){
    for (int j = 0; j < 3; j++ ){
        buf(n,i,j,0) = -0.5;
        buf(n,i,j,1) = 0.5;
        buf(n,i,j,2) = 1.5;
    }}
    CPL::ndArray<double> nodesz = field.celltonode(buf, n, 0, 0, 0);
    trplefor(icell-1,jcell-1,kcell-1){
        //std::cout << "nodez = " << i << " " << j << " " << k << " " 
        //                        << nodesz(n,i,j,k) << "\n"; 
        ASSERT_DOUBLE_EQ(nodesz(n,i,j,k), float(k));

    }}}

};

//Test for CPL::interpolate 
TEST_F(CPL_interp_Test, test_interpolate) {

    int nd = 3;
    int icell = 3;
    int jcell = 3;
    int kcell = 3;
    double *xi;

    CPL::ndArray<double> buf;
    int shape[4] = {nd, icell, jcell, kcell};
    buf.resize (4, shape);

    //Test define
    int n = 0;
    CPL::CPLField field(buf);

    //Slabs in x
    for (int j = 0; j < jcell; j++ ){
    for (int k = 0; k < kcell; k++ ){
        buf(n,0,j,k) = -0.5;
        buf(n,1,j,k) = 0.5;
        buf(n,2,j,k) = 1.5;
    }}

    //Hardwire some values
    xi = new double[3];
    xi[0] = 0.8; xi[1] = 0.2; xi[2] = 0.1;

    int order = 2;
    std::vector<double> zi = field.interpolate(xi, buf, n, order);



}


