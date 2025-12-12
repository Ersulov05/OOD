import type { TransformData } from "./types"
import styles from './ShapeView.module.css'
import type { IReadShape } from "../models/Shape/Shape"

type ShapeViewProps = {
    shape: IReadShape
    tempTransform: TransformData
    selectShape: () => void
    addToSelection: () => void
}

function ShapeView({
    shape,
    tempTransform,
    selectShape,
    addToSelection,
}: ShapeViewProps) {
    const handleShapeClick = (e: React.MouseEvent) => {
        if (e.ctrlKey || e.metaKey) {
            e.stopPropagation()
            addToSelection()
        } else {
            e.stopPropagation()
            selectShape()
        }
    }

    return (
        <svg xmlns="http://www.w3.org/2000/svg"
            className={styles.shape}
            style={{
                width: shape.getSize().width * tempTransform.sizeScale.width + 'px',
                height: shape.getSize().height * tempTransform.sizeScale.height + 'px',
                top: shape.getPosition().y + tempTransform.deltaPos.y + 'px',
                left: shape.getPosition().x + tempTransform.deltaPos.x + 'px',
            }}
        >
            {(() => {
                switch (shape.getType()) {
                    case 'rectangle':
                        return <RectView shape={shape} tempTransform={tempTransform} onClick={handleShapeClick} />
                    case 'ellipse':
                        return <EllipseView shape={shape} tempTransform={tempTransform} onClick={handleShapeClick} />
                    case 'triangle':
                        return <TriangleView shape={shape} tempTransform={tempTransform} onClick={handleShapeClick} />
                    default:
                        return null
                }
            })()}
        </svg>
    )
}

type ObjectViewProps = {
    shape: IReadShape,
    tempTransform: TransformData,
    onClick: (e: React.MouseEvent) => void
}

function RectView({
    shape,
    tempTransform,
    onClick,
}: ObjectViewProps) {
    const size = shape.getSize()
    const style = shape.getStyle()

    const rectProps = {
        x: style.thrikness,
        y: style.thrikness,
        width: size.width * tempTransform.sizeScale.width - style.thrikness * 2,
        height: size.height * tempTransform.sizeScale.height - style.thrikness * 2,
        fill: style.fillColor,
        stroke: style.outlineColor,
        strokeWidth: style.thrikness,
    }

    return (<rect
        onClick={onClick}
        {...rectProps}
    />)
}

function TriangleView({
    shape,
    tempTransform,
    onClick,
}: ObjectViewProps) {
    const size = shape.getSize()
    const style = shape.getStyle()

    const width = size.width * tempTransform.sizeScale.width - style.thrikness
    const height = size.height * tempTransform.sizeScale.height - style.thrikness

    const points = [
        `${style.thrikness},${height}`,
        `${width},${height}`,
        `${width / 2},${style.thrikness}`
    ].join(' ')

    return (
        <polygon
            onClick={onClick}
            points={points}
            fill={style.fillColor}
            stroke={style.outlineColor}
            strokeWidth={style.thrikness}
        />
    )
}

function EllipseView({
    shape,
    tempTransform,
    onClick,
}: ObjectViewProps) {
    const transformedWidth = shape.getSize().width * tempTransform.sizeScale.width
    const transformedHeight = shape.getSize().height * tempTransform.sizeScale.height
    const rx = transformedWidth / 2
    const ry = transformedHeight / 2
    const thrikness = 5;
    const style = shape.getStyle()

    const ellipseProps = {
        rx: rx - thrikness,
        ry: ry - thrikness,
        cx: rx,
        cy: ry,
        fill: style.fillColor,
        stroke: style.outlineColor,
        strokeWidth: style.thrikness
    }

    return (<ellipse
        onClick={onClick}
        {...ellipseProps}
    />)
}

export {
    ShapeView
}