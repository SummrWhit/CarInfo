// file - main.qml

import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtDataVisualization 1.0
import "."

Window {
    visible: true
    width: 1500
    height: 1080
    title: qsTr("Hello Car")
    color: "#F1F3F2"

    Carspeed {
        id: speed_car
        x: 100
        y: 50
        width: 291
        height: 238
        dial_addR: -6
        dial_longNum: 10
        dial_longLen: 15
        dial_lineWidth: 3
        btm_lineWidth: 22
        top_lineWidth: 20
        top_endAngle: DATAMGR.getSpeed()*1.3+140
        top_startAngle: 140
        btm_endAngle: 400
        btm_startAngle: 140
        btm_r: 120
        top_r: 120

        Label {
            id: label1
            x: 9
            y: 235
            width: 23
            height: 25
            text: qsTr("0")
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
        }

        Label {
            id: label2
            x: 264
            y: 235
            width: 33
            height: 25
            text: qsTr("200")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label3
            x: -27
            y: 172
            width: 23
            height: 25
            text: qsTr("20")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label4
            x: 292
            y: 171
            width: 42
            height: 25
            text: qsTr("180")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label5
            x: -28
            y: 99
            width: 23
            height: 25
            text: qsTr("40")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label6
            x: 302
            y: 99
            width: 23
            height: 25
            text: qsTr("160")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label7
            x: -2
            y: 30
            width: 23
            height: 25
            text: qsTr("60")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label8
            x: 271
            y: 30
            width: 35
            height: 25
            text: qsTr("140")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label9
            x: 62
            y: -20
            width: 23
            height: 25
            text: qsTr("80")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label10
            x: 208
            y: -21
            width: 36
            height: 25
            text: qsTr("120")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Label {
            id: label11
            x: 136
            y: -31
            width: 23
            height: 25
            text: qsTr("100")
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 14
            font.weight: Font.Normal
        }

        Text {
            id: speed
            x: 104
            y: 116
            width: 89
            height: 44
            //text: DATAMGR.getSpeed()/*slider.value*/
            style: Text.Normal
            font.weight: Font.ExtraBold
            font.capitalization: Font.AllUppercase
            font.pixelSize: 40
            font.bold: true
            font.family: "Verdana"
            horizontalAlignment: Text.AlignHCenter
        }

        Timer {
            id: timer
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                var val = DATAMGR.getSpeed()
                speed.text = val
                speed_car.top_endAngle = val*1.3+140
                if(val < 60) {
                    speed.color = "black"
                }
                else if(val<120) {
                    speed.color = "#f2ac28"
                }
                else {
                    speed.color = "red"
                }
                speed_label.color = speed.color
            }
        }


        Label {
            id: speed_label
            x: 131
            y: 154
            width: 45
            height: 30
            text: qsTr("Km/h")
            font.pointSize: 11
            font.bold: true
            verticalAlignment: Text.AlignBottom
        }
    }

    Steerwheel {
        id: steer_car
        x: 100
        y: 395
        width: 291
        height: 299
    }

    Text {
        id: acceleration
        x: 100
        y: 783
        width: 291
        height: 172

        text: "Acceleration(m/s*s)"
        fontSizeMode: Text.FixedSize
        bottomPadding: 0
        padding: 22
        topPadding: 0
        rightPadding: 20
        style: Text.Normal
        font.weight: Font.Normal
        font.family: "ubuntu"
        font.bold: false
        font.pointSize: 33
    }

    Text {
        id: acc_val
        x: 100
        y: 876
        width: 291
        height: 49
        //text: qsTr("Text")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 40
    }

    Timer {
        id: acc_timer
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            var acc = DATAMGR.getAcceleration()
            acc_val.text = acc
        }
    }

    Data {
        id: seriesData
    }

    Theme3D {
        id: themeIsabelle
        type: Theme3D.ThemeRetro
        font.family: "Lucida Handwriting"
        font.pointSize: 80
    }

    Item {
        id: dataView
        x: 600
        y: 199
        //anchors.bottom: parent.bottom
        //! [9]
        width: 848
        height: 775
        //anchors.bottomMargin: 83
        //! [8]

        //! [2]
        Scatter3D {
            id: scatterGraph
            x: 0
            y: -24
            width: 847
            height: 800
            //! [2]
            //! [3]
            theme: themeIsabelle
            shadowQuality: AbstractGraph3D.ShadowQualitySoftLow
            //! [3]
            //! [6]
            //axisX.segmentCount: 3
            //axisX.subSegmentCount: 2
            //axisX.labelFormat: "%.2f"
            //axisZ.segmentCount: 2
            //axisZ.subSegmentCount: 2
            //axisZ.labelFormat: "%.2f"
            //axisY.segmentCount: 2
            //axisY.subSegmentCount: 2
            //axisY.labelFormat: "%.2f"
            //! [6]
            //! [5]
            Scatter3DSeries {
                id: scatterSeries
                //! [5]
                //! [10]
                itemLabelFormat: "Series 1: X:@xLabel Y:@yLabel Z:@zLabel"
                //! [10]

                //! [11]
                ItemModelScatterDataProxy {
                    itemModel: seriesData.model
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
                //! [11]
            }

            //! [12]
            Scatter3DSeries {
                id: scatterSeriesTwo
                itemLabelFormat: "Series 2: X:@xLabel Y:@yLabel Z:@zLabel"
                itemSize: 0.1
                mesh: Abstract3DSeries.MeshCube
                //! [12]

                ItemModelScatterDataProxy {
                    itemModel: seriesData.modelTwo
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
            }
            Scatter3DSeries {
                id: scatterSeriesThree
                itemLabelFormat: "Series 3: X:@xLabel Y:@yLabel Z:@zLabel"
                itemSize: 0.2
                mesh: Abstract3DSeries.MeshMinimal

                ItemModelScatterDataProxy {
                    itemModel: seriesData.modelThree
                    xPosRole: "xPos"
                    yPosRole: "yPos"
                    zPosRole: "zPos"
                }
            }
        }
    }
}
