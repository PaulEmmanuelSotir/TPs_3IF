package shared;

/**
 * Classe générique regroupant deux objets de type 'L' et 'R' pour former une paire.
 */
public class Pair<L,R> {

    public Pair(L left, R right) {
        this.first = left;
        this.second = right;
    }

    @Override
    public int hashCode() { return first.hashCode() ^ second.hashCode(); }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Pair))
            return false;
        Pair other = (Pair)obj;
        // TODO: if first or sencond == null...
        return first.equals(other.first) && second.equals(other.second);
    }

    public final L first;
    public final R second;
}