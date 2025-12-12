import type { DocumentModel } from "../models/Document";
import type { DocumentEditor } from "../models/DocumentEditor";
import type { IReadShape, IShape, ShapeType } from "../models/Shape/Shape";
import { ShapeFactory } from "../models/Shape/ShapeFactory";
import type { Style } from "../models/Shape/Style";
import type { Position, Size } from "../models/types";

type SerializedShape = {
    id: string
    type: ShapeType
    position: Position
    size: Size
    style: Style
}


class SaveLoader {
    public static saveDocument(document: DocumentModel): string {
        const shapes = document.getShapes()

        const serializedShapes: SerializedShape[] = shapes.map(shape => 
            this.serializeShape(shape)
        );
        
        return JSON.stringify(serializedShapes, null, 2);
    }

    public static loadDocument(documentEditor: DocumentEditor, json: string): void {
        try {
            const shapes: SerializedShape[] = JSON.parse(json);
            if (!shapes || !Array.isArray(shapes)) {
                throw new Error("Некорректный формат документа");
            }
            
            shapes.forEach(shape => {
                if (!this.validateShape(shape)) {
                    throw new Error("Некорректный формат документа");
                }
            });
            documentEditor.loadShapes(shapes.map(shape => this.deserializeShape(shape)))
            
        } catch (error) {
            console.error("Ошибка при загрузке документа:", error);
            throw new Error("Не удалось загрузить документ");
        }
    }

    private static deserializeShape(shape: SerializedShape): IShape {
        return ShapeFactory.createShape(
            shape.id,
            shape.type,
            shape.size,
            shape.position
        )
    }

    private static serializeShape(shape: IReadShape): SerializedShape {
        return {
            id: shape.getId(),
            type: shape.getType(),
            position: { ...shape.getPosition() },
            size: { ...shape.getSize() },
            style: { ...shape.getStyle() }
        };
    }

    private static validateShape(shape: any): shape is SerializedShape {
        return (
            shape &&
            typeof shape.id === 'string' &&
            ['rectangle', 'ellipse', 'triangle'].includes(shape.type) &&
            this.validatePosition(shape.position) &&
            this.validateSize(shape.size) &&
            this.validateStyle(shape.style)
        );
    }
    
    private static validatePosition(pos: any): pos is Position {
        return (
            pos &&
            typeof pos.x === 'number' &&
            typeof pos.y === 'number'
        );
    }
    
    private static validateSize(size: any): size is Size {
        return (
            size &&
            typeof size.width === 'number' &&
            typeof size.height === 'number' &&
            size.width > 0 &&
            size.height > 0
        );
    }
    
    private static validateStyle(style: any): style is Style {
        return (
            style &&
            typeof style.fillColor === 'string' &&
            typeof style.outlineColor === 'string' &&
            typeof style.thrikness === 'number' &&
            style.thrikness >= 0
        );
    }
}

export {
    SaveLoader
}