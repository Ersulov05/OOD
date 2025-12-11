import { useEffect, useState } from "react"
import type { DocumentController } from "../controller/DocumentController"
import styles from './DocumentView.module.css'
import { Selection } from "./Selection"
import { defaulTransformData, type TransformData } from "./types"
import { ShapeView } from "./ShapeView"

type DocumentViewProps = {
    controller: DocumentController
}

function DocumentView({
    controller
}: DocumentViewProps) {
    const [shapes, setShapes] = useState(controller.getShapes())
    const [selectedShapeIds, setSelectedShapeIds] = useState<string[]>([])
    const [transformData, setTransformData] = useState<TransformData>(defaulTransformData)

    useEffect(() => {
        const handleModelChange = () => {
            setShapes(controller.getShapes())
        }

        controller.subscribe(handleModelChange)
        return () => { }
    }, [controller])

    function addShapeToSelection(shapeId: string) {
        setSelectedShapeIds(prev => [...prev, shapeId])
    }

    const selectedShapes = selectedShapeIds.length > 0
        ? shapes.filter(shape =>
            selectedShapeIds.includes(shape.getId())
        )
        : [];

    const onSaveTransform = (transform: TransformData) => {
        controller.transformShapes(selectedShapeIds, transform.deltaPos, transform.sizeScale)
        setTransformData(defaulTransformData)
    }

    return (
        <div className={styles.documentContainer}>
            <div className={styles.documentMenu}>
                <button onClick={() => controller.addShape('rectangle')}>
                    Rectangle
                </button>
                <button onClick={() => controller.addShape('ellipse')}>
                    Ellipse
                </button>
                <button onClick={() => controller.addShape('triangle')}>
                    Triangle
                </button>

                <button onClick={() => controller.setShapesFillColor(selectedShapeIds, 'red')}>
                    Red
                </button>
                <button onClick={() => {
                    controller.deleteShapes(selectedShapeIds)
                    setSelectedShapeIds([])
                }}>
                    delete
                </button>

                <button onClick={() => controller.undo()}>
                    undo
                </button>
                <button onClick={() => controller.redo()}>
                    redo
                </button>

            </div>
            <div
                className={styles.canvas}
                onClick={(e) => {
                    if (e.target === e.currentTarget) {
                        setSelectedShapeIds([])
                    }
                }}
            >
                {shapes.map(shape => (
                    <ShapeView
                        key={shape.getId()}
                        shape={shape}
                        tempTransform={selectedShapeIds.includes(shape.getId()) ? transformData : defaulTransformData}
                        selectShape={() => setSelectedShapeIds([shape.getId()])}
                        addToSelection={() => addShapeToSelection(shape.getId())}
                    />
                ))}
                <Selection
                    selectedShapes={selectedShapes}
                    tempTransform={transformData}
                    handleTransform={(transform: TransformData) => setTransformData(transform)}
                    onSaveTransform={(transform: TransformData) => onSaveTransform(transform)}
                />
            </div>
        </div>
    )
}

export {
    DocumentView
}