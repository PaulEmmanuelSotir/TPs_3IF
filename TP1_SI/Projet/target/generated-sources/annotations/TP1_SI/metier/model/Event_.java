package TP1_SI.metier.model;

import TP1_SI.metier.model.Activite;
import TP1_SI.metier.model.Adherent;
import TP1_SI.metier.model.Lieu;
import java.sql.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.ListAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2016-03-22T14:44:02")
@StaticMetamodel(Event.class)
public class Event_ { 

    public static volatile SingularAttribute<Event, Long> id;
    public static volatile ListAttribute<Event, Adherent> adherents;
    public static volatile SingularAttribute<Event, Lieu> lieu;
    public static volatile SingularAttribute<Event, Activite> activite;
    public static volatile SingularAttribute<Event, Date> date;
    public static volatile SingularAttribute<Event, Boolean> complet;

}