#include <vtkSetGet.h>
#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkBoxWidget.h>
#include <vtkBoxWidget2.h>
#include <vtkBoxRepresentation.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCommand.h>
#include <vtkTransform.h>
#include <iostream>
#include <vtkInteractorStyleDrawPolygon.h>
template<typename T>
using sp = vtkSmartPointer<T>;

class vtkMyCallBack : public vtkCommand
{
public:
    static vtkMyCallBack* New()
    {
        return new vtkMyCallBack;
    }
    virtual void Execute(vtkObject* caller, unsigned long, void*)
    {
#if 0
        auto boxWidget = dynamic_cast<vtkBoxWidget2*>(caller);
        auto t = sp<vtkTransform>::New();
        auto scale = t->GetScale();
        auto x = scale[0];
        auto y = scale[1];
        auto z = scale[2];

        if (!isCorrectScale(x)) {
            if (x < lessValue_)
            {
                scale[0] = lessValue_;
                m_actor->SetScale(lessValue_, scale[1], scale[2]);
                isCorrect_ = false;
                return;
            }
        }
        else {
            isCorrect_ = true;
        }

        std::cout << "x: " << x << "\ty: " << y << "\tz: " << z << "\n";

        dynamic_cast<vtkBoxRepresentation*>(boxWidget->GetRepresentation())->GetTransform(t);
        
        m_actor->SetUserTransform(t);
#else
        auto t = sp<vtkTransform>::New();
        auto widget = reinterpret_cast<vtkBoxWidget*>(caller);
        widget->GetTransform(t);
        auto scale = t->GetScale();
        auto x = scale[0];
        auto y = scale[1];
        auto z = scale[2];

        std::cout << "x: " << x << "\ty: " << y << "\tz: " << z << "\n";
        if (!isCorrectScale(x)) {
            if (x <= lessValue_)
            {
                scale[0] = lessValue_;
                m_actor->SetScale(lessValue_, scale[1], scale[2]);
                isCorrect_ = false;
                return;
            }
        }
        else {
            isCorrect_ = true;
        }
        std::cout << "x: " << scale[0] << "\ty: " << scale[1] << "\tz: " << scale[2] << "\n";
        if (!isCorrect_) {
            t->Scale(scale);
            widget->SetTransform(t);
            return;
        }
        widget->GetProp3D()->SetUserTransform(t);
#endif
    }

    void SetActor(sp<vtkActor> actor)
    {
        m_actor = actor;
    }

private:
    bool isCorrectScale(const double scale)
    {
        return scale >= lessValue_ && scale <= higherValue_;
    }
private:
    sp<vtkActor> m_actor;
    const double lessValue_{ 0.5 };
    const double higherValue_{ 2.0 };
    bool isCorrect_{ false };
};

int main(int vtkNotUsed( argc ), char* vtkNotUsed( argv ) [])
{
    auto cone = sp<vtkConeSource>::New();

    auto coneMapper = sp<vtkPolyDataMapper>::New();
    coneMapper->SetInputConnection(cone->GetOutputPort());

    auto coneActor = sp<vtkActor>::New();
    coneActor->SetMapper(coneMapper);

    auto renderer = sp<vtkRenderer>::New();
    renderer->AddActor( coneActor );
    renderer->SetBackground(0.1, 0.2, 0.4);

    auto window = sp<vtkRenderWindow>::New();
    window->AddRenderer(renderer);
    window->SetSize(800, 600);

    auto interactor = sp<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    auto style = sp<vtkInteractorStyleTrackballCamera>::New();
    //auto style = sp<vtkInteractorStyleDrawPolygon>::New(); //vtkInteractorStyleTrackballActor ,vtkInteractorStyleJoystickActor, vtkInteractorStyleFlight, vtkInteractorStyleRubberBand3D, vtkInteractorStyleRubberBand2D, vtkInteractorStyle3D, vtkInteractorStyle3D , vtkInteractorStyleUnicam , vtkInteractorStyleImage , vtkInteractorStyleTerrain
    interactor->SetInteractorStyle(style);

    //auto boxWidget = sp<vtkBoxWidget2>::New();
    //boxWidget->SetInteractor(interactor);
    //boxWidget->GetRepresentation()->SetPlaceFactor(0.5); // Default is 0.5
    //boxWidget->GetRepresentation()->PlaceWidget(coneActor->GetBounds());

    auto boxWidget = sp<vtkBoxWidget>::New();
    boxWidget->SetInteractor(interactor);

    boxWidget->SetProp3D(coneActor);
    boxWidget->SetPlaceFactor(1); // Make the box 1.25x larger than the actor
    boxWidget->PlaceWidget();

    auto callback = sp<vtkMyCallBack>::New();
    callback->SetActor(coneActor);
    boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

    boxWidget->On();

    window->Render();
    interactor->Start();

    return 0;
}