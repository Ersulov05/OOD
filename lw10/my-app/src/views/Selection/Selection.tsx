import { useDragAndDrop } from "../hooks/useDragAndDrop"
import styles from './Selection.module.css'
import type { Position, Size } from "../../models/types"
import { type SelectionData, type TransformData } from "../types"
import type { IReadShape } from "../../models/Shape/Shape"

type SelectionProps = {
    selectedShapes: IReadShape[]
    tempTransform: TransformData
    handleTransform: (transform: TransformData) => void,
    onSaveTransform: (transform: TransformData) => void,
}

type SelectionItemProps = {
    selectedShape: IReadShape
    tempTransform: TransformData
    minSizeScale: Size
    translateBorder: TranslateBorder
    onTransform: (transform: TransformData) => void
    onSaveTransform: (transform: TransformData) => void
}

function SelectionItem({
    selectedShape,
    tempTransform,
    minSizeScale,
    translateBorder,
    onTransform,
    onSaveTransform,
}: SelectionItemProps) {
    const onRightDownDrag = (x: number, y: number) => {
        onTransform(getRightDownDrag(x, y))
    }

    const onSaveRightDownDrag = (x: number, y: number) => {
        onSaveTransform(getRightDownDrag(x, y))
    }

    const getRightDownDrag = (x: number, y: number): TransformData => {
        x = Math.min(translateBorder.rightDx, x)
        y = Math.min(translateBorder.bottomDy, y)
        const currWidth = selectedShape.getSize().width
        const currHeight = selectedShape.getSize().height

        const sizeScale: Size = {
            width: Math.max((currWidth + x) / currWidth, minSizeScale.width),
            height: Math.max(((currHeight + y) / currHeight), minSizeScale.height),
        }
        const deltaPos: Position = { x: 0, y: 0 }

        return { deltaPos, sizeScale, origSize: selectedShape.getSize() }
    }

    const onRightUpDrag = (x: number, y: number) => {
        onTransform(getRightUpDrag(x, y))
    }

    const onSaveRightUpDrag = (x: number, y: number) => {
        onSaveTransform(getRightUpDrag(x, y))
    }

    const getRightUpDrag = (x: number, y: number): TransformData => {
        x = Math.min(translateBorder.rightDx, x)
        y = Math.max(y, -translateBorder.topDy)
        const currWidth = selectedShape.getSize().width
        const currHeight = selectedShape.getSize().height
        const widthScale = Math.max((currWidth + x) / currWidth, minSizeScale.width)
        const heightScale = Math.max(((currHeight - y) / currHeight), minSizeScale.height)
        const dy = -(heightScale * currHeight - currHeight)

        const sizeScale: Size = {
            width: widthScale,
            height: heightScale,
        }
        const deltaPos: Position = { x: 0, y: dy }

        return { deltaPos, sizeScale, origSize: selectedShape.getSize() }
    }

    const onLeftUpDrag = (x: number, y: number) => {
        onTransform(getLeftUpDrag(x, y))
    }

    const onSaveLeftUpDrag = (x: number, y: number) => {
        onSaveTransform(getLeftUpDrag(x, y))
    }

    const getLeftUpDrag = (x: number, y: number): TransformData => {
        x = Math.max(x, -translateBorder.leftDx)
        y = Math.max(y, -translateBorder.topDy)
        const currWidth = selectedShape.getSize().width
        const currHeight = selectedShape.getSize().height
        const widthScale = Math.max((currWidth - x) / currWidth, minSizeScale.width)
        const heightScale = Math.max(((currHeight - y) / currHeight), minSizeScale.height)
        const dx = -(widthScale * currWidth - currWidth)
        const dy = -(heightScale * currHeight - currHeight)

        const sizeScale: Size = {
            width: widthScale,
            height: heightScale,
        }
        const deltaPos: Position = { x: dx, y: dy }

        return { deltaPos, sizeScale, origSize: selectedShape.getSize() }
    }

    const getLeftDownDrag = (x: number, y: number): TransformData => {
        x = Math.max(x, -translateBorder.leftDx)
        y = Math.min(translateBorder.bottomDy, y)
        const currWidth = selectedShape.getSize().width
        const currHeight = selectedShape.getSize().height
        const widthScale = Math.max((currWidth - x) / currWidth, minSizeScale.width)
        const heightScale = Math.max(((currHeight + y) / currHeight), minSizeScale.height)
        const dx = -(widthScale * currWidth - currWidth)

        const sizeScale: Size = {
            width: widthScale,
            height: heightScale,
        }
        const deltaPos: Position = { x: dx, y: 0 }

        return { deltaPos, sizeScale, origSize: selectedShape.getSize() }
    }

    const onLeftDownDrag = (x: number, y: number) => {
        onTransform(getLeftDownDrag(x, y))
    }

    const onSaveLeftDownDrag = (x: number, y: number) => {
        onSaveTransform(getLeftDownDrag(x, y))
    }

    const getDrag = (x: number, y: number): TransformData => {
        x = Math.max(Math.min(translateBorder.rightDx, x), -translateBorder.leftDx)
        y = Math.max(Math.min(translateBorder.bottomDy, y), -translateBorder.topDy)
        const deltaPos: Position = { x: x, y: y }
        const sizeScale: Size = { width: 1, height: 1 }
        return { deltaPos, sizeScale, origSize: selectedShape.getSize() }
    }

    const onDrag = (x: number, y: number) => {
        onTransform(getDrag(x, y))
    }

    const onSaveDrag = (x: number, y: number) => {
        onSaveTransform(getDrag(x, y))
    }

    const leftUpPoint = useDragAndDrop(onSaveLeftUpDrag, onLeftUpDrag)
    const rightUpPoint = useDragAndDrop(onSaveRightUpDrag, onRightUpDrag)
    const leftDownPoint = useDragAndDrop(onSaveLeftDownDrag, onLeftDownDrag)
    const rightDownPoint = useDragAndDrop(onSaveRightDownDrag, onRightDownDrag)
    const drag = useDragAndDrop(onSaveDrag, onDrag)

    const selectionData = getSelectionData(selectedShape, tempTransform)
    return (
        <div className={styles.selection}>
            <div
                className={styles.vLine}
                style={{
                    left: selectionData.left + 'px',
                    top: selectionData.top + 'px',
                    height: selectionData.bottom - selectionData.top + 'px'
                }}
                onMouseDown={drag.startDrag}
            />
            <div
                className={styles.vLine}
                style={{
                    left: selectionData.right + 'px',
                    top: selectionData.top + 'px',
                    height: selectionData.bottom - selectionData.top + 'px'
                }}
                onMouseDown={drag.startDrag}
            />
            <div
                className={styles.hLine}
                style={{
                    left: selectionData.left + 'px',
                    top: selectionData.top + 'px',
                    width: selectionData.right - selectionData.left + 'px'
                }}
                onMouseDown={drag.startDrag}
            />
            <div
                className={styles.hLine}
                style={{
                    left: selectionData.left + 'px',
                    top: selectionData.bottom + 'px',
                    width: selectionData.right - selectionData.left + 'px'
                }}
                onMouseDown={drag.startDrag}
            />

            <div
                className={styles.point}
                style={{
                    left: selectionData.left + 'px',
                    top: selectionData.top + 'px'
                }}
                onMouseDown={leftUpPoint.startDrag}
            ></div>
            <div
                className={styles.point}
                style={{
                    left: selectionData.right + 'px',
                    top: selectionData.top + 'px'
                }}
                onMouseDown={rightUpPoint.startDrag}
            ></div>
            <div
                className={styles.point}
                style={{
                    left: selectionData.right + 'px',
                    top: selectionData.bottom + 'px'
                }}
                onMouseDown={rightDownPoint.startDrag}
            ></div>
            <div
                className={styles.point}
                style={{
                    left: selectionData.left + 'px',
                    top: selectionData.bottom + 'px'
                }}
                onMouseDown={leftDownPoint.startDrag}
            ></div>
        </div>
    )
}

function Selection({
    selectedShapes,
    tempTransform,
    handleTransform,
    onSaveTransform,
}: SelectionProps) {
    const minSizeScale = getMinSizeScale(selectedShapes)
    const translateBorder = getTranslateBorder(selectedShapes)
    return (
        <>
            {selectedShapes.map(shape => {
                return (
                    <SelectionItem
                        key={shape.getId()}
                        selectedShape={shape}
                        tempTransform={tempTransform}
                        minSizeScale={minSizeScale}
                        translateBorder={translateBorder}
                        onTransform={handleTransform}
                        onSaveTransform={onSaveTransform}
                    />
                )
            })}
        </>
    )
}


const MIN_SIZE = 50;
function getMinSizeScale(selectedShapes: IReadShape[]): Size {
    const minSizeScale: Size = {
        width: 0,
        height: 0
    }
    selectedShapes.forEach(shape => {
        const widthScale = MIN_SIZE / shape.getSize().width
        const heightScale = MIN_SIZE / shape.getSize().height

        if (minSizeScale.width < widthScale) {
            minSizeScale.width = widthScale
        }

        if (minSizeScale.height < heightScale) {
            minSizeScale.height = heightScale
        }
    })

    return minSizeScale
}

type TranslateBorder = {
    leftDx: number,
    rightDx: number,
    topDy: number,
    bottomDy: number,
}

const CANVAS_SIZE = 500;

function getTranslateBorder(selectedShapes: IReadShape[]): TranslateBorder {
    const translateBorder: TranslateBorder = {
        leftDx: Infinity,
        rightDx: Infinity,
        topDy: Infinity,
        bottomDy: Infinity,
    }
    selectedShapes.forEach(shape => {
        const lefDx = shape.getPosition().x
        const rightDx = CANVAS_SIZE - shape.getPosition().x - shape.getSize().width
        const topDy = shape.getPosition().y
        const bottomDy = CANVAS_SIZE - shape.getPosition().y - shape.getSize().height
        if (translateBorder.leftDx > lefDx) {
            translateBorder.leftDx = lefDx
        }
        if (translateBorder.rightDx > rightDx) {
            translateBorder.rightDx = rightDx
        }
        if (translateBorder.topDy > topDy) {
            translateBorder.topDy = topDy
        }
        if (translateBorder.bottomDy > bottomDy) {
            translateBorder.bottomDy = bottomDy
        }
    })

    return translateBorder
}

function getSelectionData(
    selectedShape: IReadShape,
    tempTransform: TransformData,
): SelectionData {
    const position = selectedShape.getPosition()
    const size = selectedShape.getSize()
    const left = position.x + tempTransform.deltaPos.x
    const top = position.y + tempTransform.deltaPos.y

    return {
        left: left,
        top: top,
        right: left + size.width * tempTransform.sizeScale.width,
        bottom: top + size.height * tempTransform.sizeScale.height,
    };
}

export {
    Selection
}