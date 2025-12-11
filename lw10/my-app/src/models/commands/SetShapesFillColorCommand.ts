import type { DocumentModel } from "../Document"
import type { ICommand } from "./ICommand"

class SetShapesFillColorCommand implements ICommand {
    constructor(documentModel: DocumentModel, shapeIds: string[], fillColor: string) {
        this.documentModel = documentModel
        this.shapeIds = shapeIds
        this.fillColor = fillColor
    }

    public execute(): void 
    {
        const shapes = this.documentModel.getShapeByIds(this.shapeIds)
        shapes.forEach(shape => {
            this.prevFillColors.set(shape.getId(), shape.getStyle().fillColor)
        })
        this.documentModel.setShapesFillColor(this.shapeIds, this.fillColor)
    }

    public unexecute(): void 
    {
        for (const [shapeId, prevFillColor] of this.prevFillColors) {
            this.documentModel.setShapesFillColor([shapeId], prevFillColor)
        }
    }

    public destruct(): void {}

    private documentModel: DocumentModel
    private shapeIds: string[]
    private fillColor: string
    private prevFillColors = new Map<string, string>()
}

export {
    SetShapesFillColorCommand
}