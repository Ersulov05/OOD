import type { Position, Size } from "../models/types"

type TransformData = {
    deltaPos: Position,
    sizeScale: Size,
    origSize: Size,
}

type SelectionData = {
    left: number,
    top: number,
    right: number,
    bottom: number,
}

const defaulTransformData = {
    deltaPos: {x: 0, y:0},
    sizeScale: {width: 1, height: 1},
    origSize: {width: 1, height: 1}
}

export {
    type TransformData,
    type SelectionData,
    defaulTransformData,
}