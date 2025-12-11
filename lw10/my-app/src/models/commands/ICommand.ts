type ICommand = {
    execute(): void,
    unexecute(): void,
    destruct(): void,
}

export {
    type ICommand,
}