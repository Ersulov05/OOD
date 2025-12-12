import { useRef } from "react";
import type { DocumentController } from "../../controller/DocumentController";
import styles from './Menu.module.css'

type MenuProps = {
    controller: DocumentController
    resetSelection: () => void
    selectedShapeIds: string[]
}

function Menu({
    controller,
    resetSelection,
    selectedShapeIds,
}: MenuProps) {
    const fileInputRef = useRef<HTMLInputElement>(null);
    const handleUploadClick = () => {
        fileInputRef.current?.click();
    };

    const handleFileSelect = async (event: React.ChangeEvent<HTMLInputElement>) => {
        const file = event.target.files?.[0];
        if (!file) return;
        try {
            const json = await file.text();
            controller.loadDocument(json)
        } catch (error) {
            console.error("Ошибка чтения файла:", error);
            alert("Не удалось прочитать файл");
        }
        if (fileInputRef.current) {
            fileInputRef.current.value = '';
        }
    };

    return (
        <div className={styles.documentMenu}>
            <button onClick={() => controller.addShape('rectangle')}>
                Rectangle
            </button>
            <button onClick={() => controller.addShape('ellipse')}>
                Ellipse
            </button>
            <button onClick={() => controller.addShape('triangle')}>
                Triangle
            </button>
            <button onClick={() => {
                const json = controller.saveDocument();
                downloadJson(json, "document.json");
            }}>
                Download
            </button>

            <button onClick={handleUploadClick}>
                Upload
            </button>

            <input
                ref={fileInputRef}
                type="file"
                accept=".json,application/json"
                style={{ display: 'none' }}
                onChange={handleFileSelect}
            />

            <button onClick={() => controller.setShapesFillColor(selectedShapeIds, 'red')}>
                Red
            </button>
            <button onClick={() => {
                controller.deleteShapes(selectedShapeIds)
                resetSelection()
            }}>
                delete
            </button>

            <button onClick={() => controller.undo()}>
                undo
            </button>
            <button onClick={() => controller.redo()}>
                redo
            </button>

        </div>
    )
}

function downloadJson(json: string, filename: string): void {
    const blob = new Blob([json], { type: "application/json" });
    const url = URL.createObjectURL(blob);

    const a = document.createElement("a");
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();

    setTimeout(() => {
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
    }, 0);
}

export {
    Menu
}