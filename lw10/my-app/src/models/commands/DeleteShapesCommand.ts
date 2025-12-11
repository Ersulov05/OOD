import type { DocumentModel } from "../Document"
import type { ICommand } from "./ICommand"

class DeleteShapesCommand implements ICommand {
    constructor(documentModel: DocumentModel, shapeIds: string[]) {
        this.documentModel = documentModel
        this.shapeIds = shapeIds
    }

    public execute(): void 
    {
        this.deletedShapeIds = this.documentModel.markShapesAsDeleted(this.shapeIds)
    }

    public unexecute(): void 
    {
        this.documentModel.recoverShapes(this.deletedShapeIds)
        this.deletedShapeIds = []
    }

    public destruct(): void
    {
        this.documentModel.removeShapes(this.deletedShapeIds)
    }

    private documentModel: DocumentModel
    private deletedShapeIds: string[] = []
    private shapeIds: string[]
}

export {
    DeleteShapesCommand
}