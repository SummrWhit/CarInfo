import QtQuick 2.0

Item {
    id: steerWheel
    width: 220
    height: 220

    Image {
        id: steer_wheel_logo
        x: 0
        y: 0
        width: steerWheel.width
        height: steerWheel.height
        source: "images.jpeg"
        NumberAnimation {
            running: steer_wheel_logo.visible
            //loops: Animation.Infinite
            target: steer_wheel_logo
            from: 0
            to: 10
            property: "rotation"
            duration: 1000
        }
    }
}
