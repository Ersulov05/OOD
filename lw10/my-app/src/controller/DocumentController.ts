import type { DocumentEditor } from "../models/DocumentEditor"
import type { IReadShape, ShapeType } from "../models/Shape/Shape"
import type { Position, Size } from "../models/types"

class DocumentController {
    constructor(documentEditor: DocumentEditor) {
        this.documentEditor = documentEditor
    }

    public subscribe(observer: () => void): void {
        this.documentEditor.subscribe(observer)
    }

    public getShapes(): IReadShape[] {
        return this.documentEditor.getDocument().getShapes()
    }

    public addShape(shapeType: ShapeType): void {
        this.documentEditor.addShape(shapeType)
    }

    public deleteShapes(shapeIds: string[]): void {
        if (shapeIds.length > 0) {
            this.documentEditor.deleteShapes(shapeIds)
        }
    }

    public transformShapes(shapeIds: string[], deltaPosition: Position, sizeScale: Size) {
        this.documentEditor.transformShapes(shapeIds, deltaPosition, sizeScale)
    }

    public setShapesFillColor(shapeIds: string[], fillColor: string): void {
        this.documentEditor.setShapesFillColor(shapeIds, fillColor)
    }

    public undo(): void {
        this.documentEditor.undo()
    }

    public redo(): void {
        this.documentEditor.redo()
    }

    private documentEditor: DocumentEditor
}

export {
    DocumentController
}