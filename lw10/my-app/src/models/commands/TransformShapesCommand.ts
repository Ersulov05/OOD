import type { DocumentModel } from "../Document"
import type { Position, Size } from "../types"
import type { ICommand } from "./ICommand"

class TransformShapesCommand implements ICommand {
    constructor(
        documentModel: DocumentModel, 
        shapeIds: string[],
        position: Position,
        sizeScale: Size,
    ) {
        this.documentModel = documentModel
        this.shapeIds = shapeIds
        this.deltaPosition = position
        this.sizeScale = sizeScale
    }

    public execute(): void 
    {
        const shapes = this.documentModel.getShapeByIds(this.shapeIds)
        
        for(const shape of shapes) {
            const position = shape.getPosition()
            const size = shape.getSize()
            const newPosition: Position = {
                x: position.x + this.deltaPosition.x,
                y: position.y + this.deltaPosition.y,
            }

            const newSize: Size = {
                width: size.width * this.sizeScale.width,
                height: size.height * this.sizeScale.height,
            }
            shape.setPosition(newPosition)
            shape.setSize(newSize)
        }
    }

    public unexecute(): void 
    {
        const shapes = this.documentModel.getShapeByIds(this.shapeIds)
        
        for(const shape of shapes) {
            const position = shape.getPosition()
            const size = shape.getSize()
            const newPosition: Position = {
                x: position.x - this.deltaPosition.x,
                y: position.y - this.deltaPosition.y,
            }

            const newSize: Size = {
                width: size.width / this.sizeScale.width,
                height: size.height / this.sizeScale.height,
            }
            shape.setPosition(newPosition)
            shape.setSize(newSize)
        }
    }

    public destruct(): void {}

    private documentModel: DocumentModel
    private shapeIds: string[]
    private deltaPosition: Position
    private sizeScale: Size
}

export {
    TransformShapesCommand,
}