import { useEffect, useRef, useState } from "react";

function useDragAndDrop(
    saveDrag?: (x: number, y: number) => void,
    handleDrag?: (x: number, y: number) => void,
) {
    const [dragging, setDragging] = useState(false);
    const startPosRef = useRef({ x: 0, y: 0 });
    const totalDeltaRef = useRef({ x: 0, y: 0 });

    const endDrag = (event: MouseEvent) => {
        event.preventDefault()
        saveDrag?.(totalDeltaRef.current.x, totalDeltaRef.current.y);
        totalDeltaRef.current = { x: 0, y: 0 };
        setDragging(false);
    };

    const onDrag = (event: MouseEvent) => {
        event.preventDefault();
        if (dragging) {
            const deltaX = event.clientX - startPosRef.current.x;
            const deltaY = event.clientY - startPosRef.current.y;

            totalDeltaRef.current.x += deltaX;
            totalDeltaRef.current.y += deltaY;

            startPosRef.current.x = event.clientX;
            startPosRef.current.y = event.clientY;

            handleDrag?.(totalDeltaRef.current.x, totalDeltaRef.current.y);
        }
    };

    useEffect(() => {
        if (dragging) {
            document.addEventListener("mousemove", onDrag);
            document.addEventListener("mouseup", endDrag);
        } else {
            document.removeEventListener("mousemove", onDrag);
            document.removeEventListener("mouseup", endDrag);
        }

        return () => {
            document.removeEventListener("mousemove", onDrag);
            document.removeEventListener("mouseup", endDrag);
        };
    }, [dragging]);

    const startDrag = (event: React.MouseEvent<HTMLDivElement>) => {
        event.preventDefault();
        event.stopPropagation();

        startPosRef.current = {
            x: event.clientX,
            y: event.clientY,
        };

        totalDeltaRef.current = { x: 0, y: 0 };

        setDragging(true);
    };

    return {
        dragging,
        startDrag,
    };
}

export {
    useDragAndDrop
}