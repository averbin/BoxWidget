cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(BoxWidget)

find_package(VTK COMPONENTS
   vtkCommonCore
   vtkCommonTransforms
   vtkFiltersSources
   #vtkInteractionStyle
   #vtkInteractionWidget
   #vtkRenderingContextOpenGL2
   vtkInteractionStyle
   vtkInteractionWidgets
   vtkRenderingOpenGL2
   vtkRenderingCore
   vtkRenderingFreeType
   vtkRenderingGL2PSOpenGL2
   vtkRenderingOpenGL2 QUIET
)

include(${VTK_USE_FILE})

if (NOT VTK_FOUND)
   message("Skipping BoxWidget: ${VTK_NOT_FOUND_MESSAGE}")
   return()
endif()

message(STATUS "VTK_VERSION: ${VTK_VERSION}")
add_executable(BoxWidget MACOSX_BUNDLE BoxWidget.cxx)
target_link_libraries(BoxWidget PRIVATE ${VTK_LIBRARIES})
vtk_module_autoinit(
    TARGETS BoxWidget
	MODULES ${VTK_LIBRARIES}
)

add_custom_command(TARGET BoxWidget POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
	"${VTK_DIR}/bin/Debug/vtkFiltersSources-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkFiltersGeneral-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkFiltersCore-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkFiltersGeometry-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkFiltersExtraction-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkFiltersStatistics-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkFiltersHybrid-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkFiltersModeling-9.0d.dll"
    "${VTK_DIR}/bin/Debug/vtkCommonCore-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonExecutionModel-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonDataModel-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonTransforms-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonComputationalGeometry-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonMath-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonMisc-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonSystem-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkCommonColor-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtksys-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkloguru-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkRenderingCore-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkRenderingAnnotation-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkRenderingFreeType-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkRenderingOpenGL2-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkRenderingUI-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkImagingColor-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkImagingCore-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkImagingGeneral-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkImagingHybrid-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkImagingSources-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkfreetype-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkzlib-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkInteractionStyle-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkglew-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkParallelDIY-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkParallelCore-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkImagingFourier-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkIOXML-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkIOXMLParser-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkIOLegacy-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkIOCore-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkdoubleconversion-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtklz4-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtklzma-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkexpat-9.0d.dll"
	"${VTK_DIR}/bin/Debug/vtkInteractionWidgets-9.0d.dll"
	$<TARGET_FILE_DIR:BoxWidget>
)