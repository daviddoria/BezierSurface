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

int main(int, char *[])
{
  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);


  // Create an arbitrary plane that we can use
  // to initialize the control points for the Bezier surface
  vtkSmartPointer<vtkPlaneSource> planeSource =
    vtkSmartPointer<vtkPlaneSource>::New();
  planeSource->SetOrigin(0,0,0);
  planeSource->SetPoint2(1,0,0);
  planeSource->SetPoint1(0,0,1);
  planeSource->SetXResolution(controlPointsX-1);
  planeSource->SetYResolution(controlPointsY-1);
  planeSource->Update();

  // Create a transformation to be applied to the Bezier surface
  vtkSmartPointer<vtkTransform> transform =
    vtkSmartPointer<vtkTransform>::New();
  transform->Scale(2,1,1);

  // Create the Bezier surface that matches the plane created above
  // and scaled by the transformation
  vtkSmartPointer<vtkBezierSurfaceSource> bezierSource =
    vtkSmartPointer<vtkBezierSurfaceSource>::New();
  bezierSource->SetNumberOfControlPoints(controlPointsX,controlPointsY);

  vtkPolyData* planePoly = planeSource->GetOutput();

  unsigned int controlPointCount = 0;
  for(unsigned int i = 0; i < controlPointsX; ++i)
    {
      for(unsigned int j = 0; j < controlPointsY; ++j)
        {
          double point[3];
          planePoly->GetPoint(i*controlPointsY+j, point);
//          std::cout << "Point " << controlPointCount << ": "
//                    << point[0] << " " << point[1] << " " << point[2] << std::endl;
          bezierSource->SetControlPoint(i,j,point);
          controlPointCount++;
        }
    }

  std::cout << "Created " << controlPointCount << " control points." << std::endl;

  bezierSource->SetTransform(transform);
  bezierSource->Update();

  vtkSmartPointer<vtkBezierSurfaceWidget> widget =
    vtkSmartPointer<vtkBezierSurfaceWidget>::New();
  widget->SetInteractor(renderWindowInteractor);
  widget->SetBezierSource(bezierSource);
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

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
