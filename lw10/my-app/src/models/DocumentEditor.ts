import { AddShapeCommand } from "./commands/AddShapeCommand"
import { DeleteShapesCommand } from "./commands/DeleteShapesCommand"
import { type ICommand } from "./commands/ICommand"
import { SetShapesFillColorCommand } from "./commands/SetShapesFillColorCommand"
import { TransformShapesCommand } from "./commands/TransformShapesCommand"
import { DocumentModel } from "./Document"
import { History } from "./History"
import type { ShapeType } from "./Shape/Shape"
import type { Position, Size } from "./types"

class DocumentEditor {
    public subscribe(observer: () => void): void {
        this.observers.push(observer)
    }

    public getDocument(): DocumentModel {
        return this.documentModel
    }

    public addShape(type: ShapeType): void {
        const command: ICommand = new AddShapeCommand(this.documentModel, type)

        this.history.execute(command)
        this.notifyObservers()
    }

    public setShapesFillColor(shapeIds: string[], fillColor: string): void {
        const command: ICommand = new SetShapesFillColorCommand(this.documentModel, shapeIds, fillColor)

        this.history.execute(command)
        this.notifyObservers()
    }

    public deleteShapes(shapeIds: string[]): void {
        const command: ICommand = new DeleteShapesCommand(this.documentModel, shapeIds)

        this.history.execute(command)
        this.notifyObservers()
    }

    public transformShapes(shapeIds: string[], deltaPosition: Position, sizeScale: Size) {
        const command: ICommand = new TransformShapesCommand(this.documentModel, shapeIds, deltaPosition, sizeScale)

        this.history.execute(command)
        this.notifyObservers()
    }

    public undo(): void {
        this.history.undo()
        this.notifyObservers()
    }

    public redo(): void {
        this.history.redo()
        this.notifyObservers()
    }

    private notifyObservers(): void {
        this.observers.forEach(observer => observer())
    }

    private documentModel: DocumentModel = new DocumentModel()
    private history: History = new History()
    private observers: Array<() => void> = []
}

export {
    DocumentEditor
}