// $Id$
//
//  Copyright (C) 2003-2006 greg Landrum and Rational Discovery LLC
//
//  @@ All Rights Reserved @@
//  This file is part of the RDKit.
//  The contents are covered by the terms of the BSD license
//  which is included in the file license.txt, found at the root
//  of the RDKit source tree.
//
#include <RDBoost/Wrap.h>
#include <DataStructs/BitVects.h>
#include <DataStructs/BitVectUtils.h>
#include <DataStructs/BitOps.h>
namespace python = boost::python;

ExplicitBitVect *createFromBitString(const std::string &bits){
    ExplicitBitVect *res=new ExplicitBitVect(bits.length());
    FromBitString(*res,bits);
    return res;
}

ExplicitBitVect *createFromFPSText(const std::string &fps){
    ExplicitBitVect *res=new ExplicitBitVect(fps.length()*4);
    UpdateBitVectFromFPSText(*res,fps);
    return res;
}


struct Utils_wrapper {
  static void wrap(){
    python::def("ConvertToExplicit", convertToExplicit, 
                python::return_value_policy<python::manage_new_object>(),
                "Converts a SparseBitVector to an ExplicitBitVector and returns the ExplicitBitVector");  
    python::def("CreateFromBitString",createFromBitString,
                python::return_value_policy<python::manage_new_object>(),
                "Creates an ExplicitBitVect from a bit string (string of 0s and 1s).");  
    python::def("CreateFromFPSText",createFromFPSText,
                python::return_value_policy<python::manage_new_object>(),
                "Creates an ExplicitBitVect from an FPS string.");  

    python::def("InitFromDaylightString",
                (void (*)(SparseBitVect &,std::string))FromDaylightString);
    python::def("InitFromDaylightString",
                (void (*)(ExplicitBitVect &,std::string))FromDaylightString,
                "Fill a BitVect using an ASCII (Daylight) encoding of a fingerprint.\n\
\n\
   **Arguments**\n\
     - bv: either a _SparseBitVect_ or an _ExplicitBitVect_\n\
     - txt: a string with the Daylight encoding (this is the text that\n\
            the Daylight tools put in the FP field of a TDT)\n\
\n");
  }
};

void wrap_Utils() {
  Utils_wrapper::wrap();
}
  
