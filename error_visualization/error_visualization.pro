TEMPLATE = app
CONFIG += debug_and_release debug_and_release_target warn_off 
DEPENDPATH += .
win32{
	CONFIG += console
	INCLUDEPATH += . "C:/Program Files/VTK/include/vtk-5.8/" "C:/Program Files/PCL/include/pcl-1.8/" "C:/Program Files/Eigen/include/eigen3/" "C:/Program Files/flann/include/" "D:/boost_1_55_0/" "C:/Program Files/CGAL/include/"
	CONFIG(debug, debug|release){
		LIBS += -L"C:/Program Files/VTK/lib/vtk-5.8/" \
			QVTK_debug.lib vtkCommon_debug.lib vtkRendering_debug.lib vtkFiltering_debug.lib vtkGraphics_debug.lib \
		-L"D:/boost_1_55_0/stage/lib/" \
			boost_system-vc100-mt-gd-1_55.lib \
		-L"C:/Program Files/PCL/lib/" \
			pcl_visualization_debug.lib pcl_io_debug.lib pcl_common_debug.lib pcl_kdtree_debug.lib pcl_search_debug.lib \
		-L"C:/Program Files/flann/lib/" \
			flann_cpp_s_debug.lib \
		-L"C:/Program Files/CGAL/lib/" \
			CGAL-vc100-mt-gd-4.5.lib CGAL_Core-vc100-mt-gd-4.5.lib CGAL_ImageIO-vc100-mt-gd-4.5.lib CGAL_Qt4-vc100-mt-gd-4.5.lib
	}else{
		LIBS += -L"C:/Program Files/VTK/lib/vtk-5.8/" \
			QVTK_release.lib vtkCommon_release.lib vtkRendering_release.lib vtkFiltering_release.lib vtkGraphics_release.lib \
		-L"D:/boost_1_55_0/stage/lib/" \
			boost_system-vc100-mt-1_55.lib \
		-L"C:/Program Files/PCL/lib/" \
			pcl_visualization_release.lib pcl_io_release.lib pcl_common_release.lib pcl_kdtree_release.lib pcl_search_release.lib \
		-L"C:/Program Files/flann/lib/" \
			flann_cpp_s_release.lib	\
		-L"C:/Program Files/CGAL/lib/" \
			CGAL-vc100-mt-4.5.lib CGAL_Core-vc100-mt-4.5.lib CGAL_ImageIO-vc100-mt-4.5.lib CGAL_Qt4-vc100-mt-4.5.lib	
	}
}
unix{
	INCLUDEPATH += . /usr/include/vtk-5.8/ /usr/local/include/pcl-1.8/ /usr/include/eigen3/
	LIBS += -L/usr/lib/ \
			-lQVTK -lvtkCommon -lQVTK -lvtkRendering -lvtkFiltering -lvtkGraphics \
			-lboost_system \
			-lCGAL -lCGAL_Core -lCGAL_ImageIO -lCGAL_Qt4 \
			-L/usr/local/lib/ \
			-lpcl_visualization -lpcl_io -lpcl_common -lpcl_kdtree -lpcl_search 
	QMAKE_CXXFLAGS += -std=c++11
}
#HEADERS += 

SOURCES += main.cpp


