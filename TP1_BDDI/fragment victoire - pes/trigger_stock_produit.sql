CREATE OR REPLACE TRIGGER FK_STOCK_PRODUIT 
BEFORE INSERT OR UPDATE ON  Stock_Amerique  
FOR EACH ROW
DECLARE
  isReferenced NUMBER;
BEGIN
  SELECT COUNT(*) INTO isReferenced
  FROM Produits
  WHERE REF_PRODUIT = :NEW.REF_PRODUIT;
  
  if(isReferenced = 0)
  THEN
    RAISE_APPLICATION_ERROR(-20003, 'REF_PRODUIT inexistant !');
  END IF;
END;