cmake_minimum_required(VERSION 2.6)

PROJECT(Bezier)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(BezierSource Example_Source.cxx vtkBezierSurfaceSource.cxx)
TARGET_LINK_LIBRARIES(BezierSource vtkHybrid)

ADD_EXECUTABLE(BezierWidget Example_Widget.cxx vtkBezierSurfaceWidget.cxx)
TARGET_LINK_LIBRARIES(BezierWidget vtkHybrid)

