import QtQuick 2.0

Rectangle{
    width: parent.width
    height: 40
    gradient: Gradient {
        GradientStop {
            position: 0.03;
            color: "#e6eeff";
        }
        GradientStop {
            position: 1.00;
            color: "#cfdefc";
        }
    }
}
