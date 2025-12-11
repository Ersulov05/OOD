import type { IReadShape, IShape } from "./Shape/Shape"

type ShapeData = {
    shape: IShape
    isDeleted?: boolean
}

class DocumentModel {
    private shapesData: ShapeData[] = []
    private shapeIndex = new Map<string, ShapeData>()

    public getShapes(): IReadShape[] {
        return this.shapesData
            .filter(shapeData => !shapeData.isDeleted)
            .map(shapeData => shapeData.shape)
    }

    public addShape(shape: IShape): void {
        const shapeData: ShapeData = {shape}
        this.shapesData.push(shapeData)
        this.indexShape(shapeData)
    }

    public removeShapes(shapeIds: string[]): void {        
        this.shapesData = this.shapesData.filter(shapeData => {
            const shapeId = shapeData.shape.getId()
            
            if (shapeIds.includes(shapeId)) {
                this.unindexShape(shapeId)
                return false
            }
            
            return true
        })
    }

    public setShapesFillColor(shapeIds: string[], fillColor: string): void {
        this.shapesData.forEach(shapeData => {
            const shapeId = shapeData.shape.getId()
            if (shapeIds.includes(shapeId) && !shapeData.isDeleted) {
                const style = shapeData.shape.getStyle()
                shapeData.shape.setStyle({
                    fillColor: fillColor,
                    outlineColor: style.outlineColor,
                    thrikness: style.thrikness,
                })
            }
        })
    }

    public setShapesOutlineColor(shapeIds: string[], outlineColor: string): void {
        this.shapesData.forEach(shapeData => {
            const shapeId = shapeData.shape.getId()
            if (shapeIds.includes(shapeId) && !shapeData.isDeleted) {
                const style = shapeData.shape.getStyle()
                shapeData.shape.setStyle({
                    fillColor: style.fillColor,
                    outlineColor: outlineColor,
                    thrikness: style.thrikness,
                })
            }
        })
    }

    public setShapesThrikness(shapeIds: string[], thrikness: number): void {
        this.shapesData.forEach(shapeData => {
            const shapeId = shapeData.shape.getId()
            if (shapeIds.includes(shapeId) && !shapeData.isDeleted) {
                const style = shapeData.shape.getStyle()
                shapeData.shape.setStyle({
                    fillColor: style.fillColor,
                    outlineColor: style.outlineColor,
                    thrikness: thrikness,
                })
            }
        })
    }

    public markShapesAsDeleted(shapeIds: string[]): string[] {
        const markedIds: string[] = []
        
        this.shapesData.forEach(shapeData => {
            const shapeId = shapeData.shape.getId()
            if (shapeIds.includes(shapeId) && !shapeData.isDeleted) {
                shapeData.isDeleted = true
                markedIds.push(shapeId)
            }
        })
        
        return markedIds
    }


    public recoverShapes(shapeIds: string[]): void {
        this.shapesData.forEach(shapeData => {
            const shapeId = shapeData.shape.getId()
            if(shapeIds.includes(shapeId)) {
                shapeData.isDeleted = false
            }
        })
    }

    public getShapeByIds(ids: string[]): IShape[] {
        const result: IShape[] = []
        
        for (const id of ids) {
            const shapeData = this.shapeIndex.get(id)

            if (shapeData && !shapeData.isDeleted) {
                result.push(shapeData.shape)
            }
        }
        
        return result
    }

    public getShapeById(id: string): IShape | undefined {
        const shapeData = this.shapeIndex.get(id)

        if (!shapeData || shapeData.isDeleted) {
            return undefined
        }
        
        return shapeData.shape
    }

    public getShapeCount(): number {
        return this.getShapes().length
    }

    private indexShape(shapeData: ShapeData): void {
        this.shapeIndex.set(shapeData.shape.getId(), shapeData)
    }

    private unindexShape(id: string): void {
        this.shapeIndex.delete(id)
    }

}

export {
    DocumentModel,
}