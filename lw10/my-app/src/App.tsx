import styles from './App.module.css'
import { DocumentController } from './controller/DocumentController'
import { DocumentView } from './views/DocumentView'
import { DocumentEditor } from './models/DocumentEditor'

function App() {
    const documentEditor: DocumentEditor = new DocumentEditor
    const controller: DocumentController = new DocumentController(documentEditor)

    return (
        <div className={styles.display}>
            <DocumentView controller={controller} />
            <DocumentView controller={controller} />
        </div>
    )
}

export default App
