/**
 * create L2Admin view
 *V_L2ADMIN
 */
CREATE OR REPLACE VIEW V_L2ADMIN AS
SELECT ID, USERNAME, PASSWORD, STATUS
FROM L2ADMIN


/**
 *CREATE  SCRIABLERS VIEW
 *V_SCRIABLERS
 */
CREATE OR REPLACE VIEW V_SCRIABLERS AS
SELECT ID, UID, EMAIL, STATUS, SUBSCRIABE
FROM SUERS
WHERE SUBSCRIABE IS NOT NULL


/**
 * CREATE V_INCIDENTS
 * V_INCIDENTS
 */
CREATE OR REPLACE VIEW V_INCIDENTS AS
SELECT ITYPE, IREPORTTIME, ICREDIT, IDESCRIPTION, OWHOADD, ILOCATION, IPRECISELOCATION, ID
FROM INCIDENT
