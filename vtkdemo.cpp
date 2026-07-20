#include <vtkActor.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNew.h>

int main() {
    vtkNew<vtkNamedColors> colors;

    // 1. Crear la geometría (Fuente)
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(200); // Número de caras del cilindro

    // 2. Mapear la geometría a primitivas gráficas
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // 3. Crear el Actor (representa el objeto en la escena)
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData());

    // 4. Configurar el Renderer y la Ventana
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(cylinderActor);
    renderer->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetWindowName("Demo VTK - Cilindro");
    renderWindow->SetSize(600, 600);
    renderWindow->AddRenderer(renderer);

    // 5. Configurar la interacción (mouse/teclado)
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // 6. Iniciar la visualización
    renderWindow->Render();
    renderWindowInteractor->Start();

    return 0;
}