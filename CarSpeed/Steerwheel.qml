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
        //rotation: 10

        Timer {
            id: wheel_timer
            interval: 1000
            repeat: true
            running: true
            onTriggered: {
                var angel = DATAMGR.getwheelAngel()
                steer_wheel_logo.rotation = angel
            }
        }
        Component.onCompleted: {
            wheel_timer.start()
        }
    }
}
