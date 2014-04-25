// Bezier surface and widget example
/*
  In this example, a Bezier surface initialized to an arbitrary plane
  is transformed (scaled) and then displayed. A widget consisting of
  a convex hull containing the surface allows the manipulation of the
  control points. These poins can be moved to deform the surface.
  Note that initialization of points and/or transformation it is not
  required.
 */

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
#include <vtkPlaneSource.h>
#include <vtkTransform.h>

#include "vtkBezierSurfaceWidget.h"
#include "vtkBezierSurfaceSource.h"

const int controlPointsX=4;
const int controlPointsY=4;

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


  //Create an arbitrary plane that we can use
  //to initialize the control points for the Bezier surface
  vtkSmartPointer<vtkPlaneSource> planeSource =
    vtkSmartPointer<vtkPlaneSource>::New();
  planeSource->SetOrigin(0,0,0);
  planeSource->SetPoint2(1,0,0);
  planeSource->SetPoint1(0,0,1);
  planeSource->SetXResolution(controlPointsX-1);
  planeSource->SetYResolution(controlPointsY-1);
  planeSource->Update();

  //Create a transformation to be applied to the Bezier surface
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Scale(2,1,1);

  //Create the Bezier surface that matches the plane created above
  //and scaled by the transformation
  vtkSmartPointer<vtkBezierSurfaceSource> bezierSource =
    vtkSmartPointer<vtkBezierSurfaceSource>::New();
  bezierSource->SetNumberOfControlPoints(controlPointsX,controlPointsY);

  vtkPolyData* planePoly = planeSource->GetOutput();

  for(int i=0; i<controlPointsX; i++)
    {
      for(int j=0; j<controlPointsY; j++)
        {
          bezierSource->SetControlPoint(i,j,planePoly->GetPoint(i*controlPointsY+j));
        }
    }
  bezierSource->SetTransform(transform);
  bezierSource->Update();

  vtkSmartPointer<vtkBezierSurfaceWidget> widget =
    vtkSmartPointer<vtkBezierSurfaceWidget>::New();
  widget->SetInteractor(renderWindowInteractor);
  widget->SetSource(bezierSource);
  widget->SetHandleSize(0.1);
  widget->On();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(bezierSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer->AddActor(actor);
  renderer->SetBackground(0.3,0.3,0.3); // Background color white

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
