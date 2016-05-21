import metier.service.Service;

/**
 *
 * @author B3330
 */
public class ClientPageAction {
    public ClientPageAction() {
        m_service = new Service();
        
    }
    
    private Service m_service;
}

            /*Enumeration names = request.getParameterNames();
            
            while(names.hasMoreElements())
            {
                String name = (String)names.nextElement();
                String[] values = request.getParameterValues(name);
                System.out.println("name : " + name + "  , values : " + values);
            }*/