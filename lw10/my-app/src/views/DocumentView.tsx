import { useEffect, useState } from "react"
import type { DocumentController } from "../controller/DocumentController"
import styles from './DocumentView.module.css'
import { Selection } from "./Selection/Selection"
import { defaulTransformData, type TransformData } from "./types"
import { ShapeView } from "./ShapeView"
import { Menu } from "./Menu/Menu"

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
            <Menu
                controller={controller}
                resetSelection={() => setSelectedShapeIds([])}
                selectedShapeIds={selectedShapeIds}
            />
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