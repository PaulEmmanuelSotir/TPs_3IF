package shared;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

/**
 * Classe permettant de faire un ObjectOutput stream qui ajoute les objets à la suite des autres dans un fichier deja existant (n'ajout pas de header)
 * @see  <a href="http://stackoverflow.com/questions/1194656/appending-to-an-objectoutputstream/1195078#1195078">Appending to an ObjectOutputStream (stack overflow)</a>
 */
public class AppendingObjectOutputStream extends ObjectOutputStream {

    /**
     * Constructeur de la classe AppendingObjectOutputStream.
     * @param  out  OutputStream à partir du quel créer l'ObjectOutputStream
     * @throws IOException
     */
    public AppendingObjectOutputStream(OutputStream out) throws IOException {
        super(out);
    }

    /**
     * Surcharge de la fonction 'writeStreamHeader()' permettant d'éviter l'éxriture d'un header au millieu du fichier binaire (ou toute autre cible avec append = true) au quel sont ajoutés les objets serialisés.
     * @throws IOException
     */
    @Override
    protected void writeStreamHeader() throws IOException {
        reset();
    }
}