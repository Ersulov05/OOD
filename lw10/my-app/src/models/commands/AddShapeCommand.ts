import type { DocumentModel } from "../Document"
import type { ShapeType } from "../Shape/Shape"
import { ShapeFactory } from "../Shape/ShapeFactory"
import type { Size } from "../types"
import type { ICommand } from "./ICommand"

class AddShapeCommand implements ICommand {
    constructor(documentModel: DocumentModel, shapeType: ShapeType) {
        this.documentModel = documentModel
        this.shapeType = shapeType
        this.shapeId = ShapeFactory.generateUID()
    }

    public execute(): void 
    {
        const size: Size = {width: 100, height: 100}
        const newShape = ShapeFactory.createShape(this.shapeId, this.shapeType, size)
        this.documentModel.addShape(newShape)
    }

    public unexecute(): void 
    {
        this.documentModel.removeShapes([this.shapeId])
    }

    public destruct(): void {}

    private documentModel: DocumentModel
    private shapeType: ShapeType
    private shapeId: string
}

export {
    AddShapeCommand
}