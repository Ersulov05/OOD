import type { ICommand } from "./commands/ICommand"

class History {
    public canUndo(): boolean {
        return this.undoStack.length > 0
    }

    public canRedo(): boolean {
        return this.redoStack.length > 0
    }

    public undo(): void {
        if (!this.canUndo()) {
            return
        }

        const command = this.undoStack.pop()!
        command.unexecute()
        this.redoStack.push(command)
    }

    public redo(): void {
        if (!this.canRedo()) {
            return
        }

        const command = this.redoStack.pop()!
        command.execute()
        this.undoStack.push(command)
    }

    public execute(command: ICommand): void {
        command.execute()
        this.undoStack.push(command)
        this.redoStack = []
        
        if (this.undoStack.length > History.MAX_SIZE) {
            const command = this.undoStack.shift()
            command?.destruct()
        }
    }

    public clear(): void {
        this.undoStack = []
        this.redoStack = []
    }

    private undoStack: ICommand[] = []
    private redoStack: ICommand[] = []
    private static readonly MAX_SIZE: number = 10
}

export {
    History
}