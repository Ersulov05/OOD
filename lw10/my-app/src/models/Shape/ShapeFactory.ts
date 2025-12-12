import type { Position, Size } from "../types";
import { Ellipse, Rectangle, Triangle, type IShape, type ShapeType } from "./Shape";
import type { Style } from "./Style";

class ShapeFactory {
    public static createShape(uid: string, shapeType: ShapeType, size: Size, position?: Position, style?: Style): IShape {
        switch (shapeType) {
            case 'rectangle':
                return new Rectangle(uid, size, position, style)
            case 'triangle':
                return new Triangle(uid, size, position, style)
            case 'ellipse':
                return new Ellipse(uid, size, position, style)
            default:
                throw new Error(`Unknown shape type: ${shapeType}`); 
        }
    }

    public static generateUID(): string {
        return Date.now().toString(36) + Math.random().toString(36).substring(2);
    }
}

export {
    ShapeFactory
}
