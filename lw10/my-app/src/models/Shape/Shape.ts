import type { Position, Size } from "../types"
import type { Style } from "./Style"

type ShapeType = 'rectangle' | 'ellipse' | 'triangle'

type IReadShape = {
    getPosition(): Readonly<Position>,
    getStyle(): Readonly<Style>,
	getSize(): Readonly<Size>,
    getType(): Readonly<ShapeType>,
    getId(): string,
}

type IShape = IReadShape & {
    setSize: (size: Size) => void,
    setPosition: (position: Position) => void,
    setStyle(style: Style): void
}

const DEFAULT_POSITION: Position = {x: 100, y: 100}
const DEFAULT_STYLE: Style = {fillColor: "#000000", outlineColor: "red", thrikness: 5}

abstract class BaseShape implements IShape {
    constructor(id: string, size: Size, position: Position = DEFAULT_POSITION, style: Style = DEFAULT_STYLE) {
		this.id = id
        this.size = size
        this.position = position
        this.style = style
	}

    public getId(): string {
        return this.id
    }
 
    public getPosition(): Readonly<Position> {
        return {
            ...this.position
        }
    }

    public getSize(): Readonly<Size> {
        return {
            ...this.size
        }
    }

    public setSize(size: Size): void {
        this.size = size
    }

    public getStyle(): Readonly<Style> {
        return this.style
    }


    public setStyle(style: Style): void {
        this.style = style
    }

    public setPosition(position: Position): void {
        this.position = position
    }

    abstract getType(): ShapeType

    private style: Style
    private position: Position
    private size: Size
    private id: string
}

class Rectangle extends BaseShape {
    public getType(): ShapeType {
        return this.type
    }

    private type: ShapeType = 'rectangle'
}

class Triangle extends BaseShape {
    public getType(): ShapeType {
        return this.type
    }

    private type: ShapeType = 'triangle'
}

class Ellipse extends BaseShape {
    public getType(): ShapeType {
        return this.type
    }

    private type: ShapeType = 'ellipse'
}

export {
    Rectangle,
    Triangle,
    Ellipse,
    type IShape,
    type IReadShape,
    type ShapeType,
}
