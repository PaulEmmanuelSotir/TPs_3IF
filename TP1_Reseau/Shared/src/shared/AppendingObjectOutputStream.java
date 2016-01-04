package shared;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

// Classe permettant de faire un ObjectOutput stream qui ajouter les objets à la suite des autre dans un fichier deja existant (n'ajout pas de header)
// voir : http://stackoverflow.com/questions/1194656/appending-to-an-objectoutputstream/1195078#1195078
public class AppendingObjectOutputStream extends ObjectOutputStream {

    public AppendingObjectOutputStream(OutputStream out) throws IOException {
        super(out);
    }

    @Override
    protected void writeStreamHeader() throws IOException {
        reset();
    }
}