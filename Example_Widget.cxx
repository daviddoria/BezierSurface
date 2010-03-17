#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkSphereWidget.h>
#include <vtkSphereRepresentation.h>
#include <vtkCommand.h>

#include "vtkBezierSurfaceWidget.h"

int main(int argc, char *argv[])
{
  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = 
      vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
      vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  vtkSmartPointer<vtkBezierSurfaceWidget> widget = 
    vtkSmartPointer<vtkBezierSurfaceWidget>::New();
  widget->SetInteractor(renderWindowInteractor);
  widget->On();
  
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
