<?php
switch($phrase) {

// Top strip
     case "Home": $tmp = "Heim"; break;
     case "About us": $tmp = "&Uuml;ber uns"; break;
     case "Partners": $tmp = "Partner"; break;
     case "Contact": $tmp = "Kontakt"; break;

     case "Logged in": $tmp = "Eingeloggt als"; break;
     case "Expires": $tmp = "Endet"; break;
     case "Not Logged in": $tmp = "Nicht eingeloggt"; break;

// Top title
     case "Open Source Business":  $tmp = "Open Source Business"; break;

// Menue bar
     case "Q&amp;A": $tmp = "F&amp;A"; break;
     case "Login": $tmp = "Einloggen"; break;
     case "Logout": $tmp = "Ausloggen"; break;
     case "New User": $tmp = "Neuer Benutzer"; break;
     case "Forgot Password": $tmp = "Passwort vergessen"; break;
     case "Change User": $tmp = "Benutzer &auml;ndern"; break;
     case "Users": $tmp = "Benutzer"; break;

     case "Enterprises": $tmp = "Unternehmen"; break;
     case "New Enterprise": $tmp = "Neues Unternehmen"; break;
     case "Update Enterprise": $tmp = "Unternehmen aktualisieren"; break;
     case "Contacts": $tmp = "Kontakte"; break;
     case "Services": $tmp = "Dienste"; break;
     case "Products": $tmp = "Produkte"; break;
     case "Solutions": $tmp = "Lösungen"; break;
     case "Customers": $tmp = "Kunden"; break;
     case "News": $tmp = "News"; break;
     case "News": $tmp = "News"; break;
     case "Comments": $tmp = "Kommentare"; break;

     case "Backend": $tmp = "$phrase"; break;
     case "Statistics": $tmp = "Statistiken"; break;

     case "Administration": $tmp = "Administration"; break;
     case "Contact Categories": $tmp = "Kontaktkategorien"; break;
     case "Service Categories": $tmp = "Dienstkategorien"; break;
     case "Product Categories": $tmp = "Produktkategorien"; break;

     case "Search": $tmp = "Suche"; break;
     case "Language": $tmp = "Sprache"; break;
     case "Go": $tmp = "Los"; break;

// Languages
	 case "English": $tmp = "Englisch"; break;
	 case "German": $tmp = "Deutsch"; break;
	 case "Spanish": $tmp = "Spanisch"; break;

// sorted by
	 case "sorted by": $tmp = "sortiert nach"; break;
	 case "Date": $tmp = "Datum"; break;
	 case "Name": $tmp = "Name"; break;
	 case "Attention": $tmp = "Beachtung"; break;
	 case "Filter": $tmp = "Filter"; break;

// navigate
	 case "Previous": $tmp = "Zurück"; break;
	 case "Top": $tmp = "Top"; break;
	 case "Next": $tmp = "Weiter"; break;

// Homepage
     case "Open Source Enterprises, Services, Products and Solutions": $tmp = "Open Source Unternehmen, Dienste, Produkte und Lösungen"; break;
     case "including Profile and Links to further Information": $tmp = "einschließlich Unternehmensprofil und Referenzen zu weiteren Informationen"; break;
     case "including Address, Phone, Email, Homepage, etc.": $tmp = "einschließlich Adresse, Telefon, Email, Homepage, etc."; break;
     case "including Consulting, Education &amp; Training, Projects, Support, etc.": $tmp = "einschließlich Consulting, Schulung &amp; Training, Projekte, Support, etc."; break;
     case "including Software, Hardware, Books, Accessories, etc.": $tmp = "einschließlich Software, Hardware, Bücher, Zubehör, etc."; break;
     case "created by Enterprises for Customers": $tmp = "erstellt von Unternehmen für Kunden"; break;
     case "of Enterprises": $tmp = "der Unternehmen"; break;
     case "provided by Enterprises": $tmp = "von Unternehmen bereitgestellt"; break;
     case "about Enterprises by Users": $tmp = "von Benutzern zu Unternehmen"; break;

// FAQ
     case "Frequently Asked Questions": $tmp = "Oft gestellte Fragen"; break;
     case "Question": $tmp = "Frage"; break;
     case "Answer": $tmp = "Antwort"; break;

// User registration
     case "Register as a new User": $tmp = "Registrierung als neuer Benutzer"; break;
     case "Username": $tmp = "Benutzername"; break;
     case "Password": $tmp = "Passwort"; break;
     case "Confirm Password": $tmp = "Passwort bestätigen"; break;
     case "Realname": $tmp = "Name"; break;
     case "Register": $tmp = "Registrieren"; break;
     case "User Registration": $tmp = "Benutzerregistrierung"; break;
     case "Congratulations": $tmp = "Gratulation"; break;
     case "You have registered on $GLOBALS[sys_name]": $tmp = "Sie haben sich bei $GLOBALS[sys_name] registriert"; break;
     case "Your new username is": $tmp = "Ihr neuer Benutzername ist"; break;
     case "You are now being sent a confirmation email to verify your email address": $tmp = "Es wurde eine Bestätigung per E-Mail an Sie gesendet, um Ihre E-Mail-Adresse zu überprüfen"; break;
     case "Visiting the link sent to you in this email will activate your account": $tmp = "Wenn Sie die in dieser E-Mail gesendete Seite besuchen wird Ihre Benutzerkennung freigeschaltet"; break;
     case "Thank you for registering on the $GLOBALS[sys_name] Site. In order": $tmp = "Danke für Ihre Registrierung bei $GLOBALS[sys_name]. Um Ihre"; break;
     case "to complete your registration, visit the following URL": $tmp = "Registrierung abzuschließen, besuchen Sie die folgende URL"; break;
     case "Enjoy the site": $tmp = "Wir hoffen, dass Ihnen $GLOBALS[sys_name] gefällt"; break;
     case " -- the $GLOBALS[sys_name] crew": $tmp = " -- die $GLOBALS[sys_name] Crew"; break;
     case "Verification of Registration": $tmp = "Verifikation der Registrierung"; break;
     case "Your account is now activated. Please login": $tmp = "Ihre Benutzerkennung ist jetzt freigeschaltet. Bitte loggen Sie sich ein"; break;

// Forget password / Remind me
     case "Register as a new User": $tmp = "Registrierung als neuer Benutzer"; break;
     case "Remind me": $tmp = "Erinnern"; break;
     case "Your Username and Password for $GLOBALS[sys_name] is": $tmp = "Ihr Benutzername und Passwort für $GLOBALS[sys_name] ist"; break;
     case "Please keep this e-mail for further reference": $tmp = "Bitte bewahren Sie diese E-Mail zur späteren Referenzierung auf"; break;
     case "You will get your Password by e-mail in a couple of minutes": $tmp = "Sie erhalten Ihr Passwort per E-Mail in wenigen Minuten"; break;
     case "Attention!": $tmp = "Achtung!"; break;

// Change User Parameters
     case "Change User Parameters": $tmp = "Änderung der Benutzerdaten"; break;
     case "Remind me": $tmp = "Erinnerung"; break;
     case "Modification": $tmp = "Modifiziert"; break;
     case "Creation": $tmp = "Erzeugt"; break;
     case "Permission": $tmp = "Rechte"; break;
     case "Change": $tmp = "Ändern"; break;
     case "Password and/or E-Mail Address of": $tmp = "Passwort und/oder E-Mail-Adresse von"; break;
     case "is changed": $tmp = "wurden geändert"; break;

// Enterprise
     case "Enterprise": $tmp = "Unternehmen"; break;
     case "by": $tmp = "von"; break;
     case "Enterprise Name": $tmp = "Name des Unternehmens"; break;
     case "Current Logofile": $tmp = "Momentanes Logofile"; break;
     case "Short Profile": $tmp = "Kurzprofil"; break;
     case "Add Comment": $tmp = "Erstelle Kommentar"; break;
     case "Keep": $tmp = "Beibehalten"; break;
     case "New": $tmp = "Neu"; break;
     case "Update": $tmp = "Aktualisiere"; break;
     case "Add": $tmp = "Erstelle"; break;
     case "Insert": $tmp = "Hinzufügen"; break;
     case "Undelete": $tmp = "Wiederherstellen"; break;
     case "active": $tmp = "aktiv"; break;
     case "deleted": $tmp = "gelöscht"; break;
     case "Deleted": $tmp = "Gelöscht"; break;
     case "Enterprise is erased": $tmp = "Unternehmen ist vernichtet"; break;
     case "Use HTML for layout": $tmp = "Benutzen Sie HTML für das Layout"; break;

// Profile
     case "Profile": $tmp = "Profil"; break;
     case "Update Profile": $tmp = "Profil aktualisieren"; break;
     case "Profile is erased": $tmp = "Profil ist vernichtet"; break;

// Contact
     case "Update Contact": $tmp = "Kontakt aktualisieren"; break;
     case "Type": $tmp = "Typ"; break;
     case "Description": $tmp = "Beschreibung"; break;
     case "Address": $tmp = "Adresse"; break;
     case "Country": $tmp = "Land"; break;
     case "State": $tmp = "Bundesland"; break;
     case "City": $tmp = "Stadt"; break;
     case "ZIP": $tmp = "PLZ"; break;
     case "Phone": $tmp = "Telefon"; break;
     case "of": $tmp = "von"; break;
     case "Contact is erased": $tmp = "Kontakt ist vernichtet"; break;

// Service
     case "Service": $tmp = "Dienst"; break;
     case "Update Service": $tmp = "Dienst aktualisieren"; break;
     case "Category": $tmp = "Kategorie"; break;
     case "Homepage": $tmp = "$phrase"; break;
     case "Service is erased": $tmp = "Dienst ist vernichtet"; break;

// Product
     case "Product": $tmp = "Produkt"; break;
     case "Update Product": $tmp = "Produkt aktualisieren"; break;
     case "Product is erased": $tmp = "Produkt ist vernichtet"; break;

// Solution
     case "Solution": $tmp = "Lösung"; break;
     case "Update Solution": $tmp = "Lösung aktualisieren"; break;
     case "Solution is erased": $tmp = "Lösung ist vernichtet"; break;

// Customer
     case "Customer": $tmp = "Kunde"; break;
     case "Update Customer": $tmp = "Kunde aktualisieren"; break;
     case "Customer is erased": $tmp = "Kunde ist vernichtet"; break;

// News
     case "News": $tmp = "$phrase"; break;
     case "Update News": $tmp = "News aktualisieren"; break;
     case "News is erased": $tmp = "News ist vernichtet"; break;

// Comment
     case "Comment": $tmp = "Kommentar"; break;
     case "Subject": $tmp = "Thema"; break;
     case "about": $tmp = "zu"; break;
     case "Comment is erased": $tmp = "Kommentar ist vernichtet"; break;

// Login
     case "$GLOBALS[sys_name] Login": $tmp = "Bei $GLOBALS[sys_name] Einloggen"; break;
     case "Welcome to $GLOBALS[sys_name]": $tmp = "Willkommen bei $GLOBALS[sys_name]"; break;
     case "You are logged in as": $tmp = "Sie sind eingeloggt als"; break;
     case "with": $tmp = "mit"; break;
     case "permission": $tmp = "Rechten"; break;
     case "Your authentication is valid until": $tmp = "Ihre Authentifizierung ist gültig bis"; break;

// Logout
     case "You have been logged in as": $tmp = "Sie waren eingeloggt als"; break;
     case "Your authentication was valid until": $tmp = "Ihre Authentifizierung war gültig bis"; break;
     case "This is all over now. You have been logged out": $tmp = "Dies ist nun vorbei. Sie haben sich ausgeloggt"; break;

// Newsletter
     case "Subscribe Newsletter": $tmp = "Newsletter abonnieren"; break;
     case "Subscribe": $tmp = "Abonnieren"; break;
     case "Send newsletter": $tmp = "Sende Newsletter"; break;
     case "Newsletter was sent at ": $tmp = "Newsletter wurde gesendet am "; break;
     case "You have subscribed to $GLOBALS[sys_name] daily Newsletter": $tmp = "Sie haben den täglichen $GLOBALS[sys_name] Newsletter abonniert"; break;
     case "You have subscribed to $GLOBALS[sys_name] weekly Newsletter": $tmp = "Sie haben den wöchentlichen $GLOBALS[sys_name] Newsletter abonniert"; break;
     case "Daily Newsletter": $tmp = "Täglicher Newsletter"; break;
     case "Weekly Newsletter": $tmp = "Wöchentlicher Newsletter"; break;
     case "daily": $tmp = "täglich"; break;
     case "weekly": $tmp = "wöchentlich"; break;

// Errors
     case "Access denied": $tmp = "Zugriff verweigert"; break;
     case "No Entry found": $tmp = "Kein Eintrag vorhanden"; break;
     case "Error": $tmp = "Fehler"; break;
     case "does not exist": $tmp = "existiert nicht"; break;
     case "Change User Parameters failed": $tmp = "Änderung der Benutzerdaten ist fehlgeschlagen"; break;
     case "No Enterprise ID specified": $tmp = "Keine Unternehmens-ID angegeben"; break;
     case "No Enterprise Name specified": $tmp = "Kein Unternehmensname angegeben"; break;
     case "Please select": $tmp = "Bitte wählen Sie"; break;
     case "and": $tmp = "und"; break;
     case "User": $tmp = "Benutzer"; break;
     case "already exists": $tmp = "existiert bereits"; break;
     case "Please select a different Username": $tmp = "Bitte wählen Sie einen anderen Benutzernamen"; break;
     case "Please enter": $tmp = "Bitte angeben:"; break;
     case "Either your Username or E-Mail Address is unknown": $tmp = "Entweder Ihr Benutzername oder E-Mail-Adresse ist unbekannt"; break;
     case "Please try again": $tmp = "Bitte versuchen Sie es nochmal"; break;
     case "If you are not yet a registered User, please select": $tmp = "Wenn Sie noch kein registrierter Benutzer sind, wählen Sie bitte"; break;
     case "Verification of Registration failed": $tmp = "Verifikation der Registrierung ist fehlgeschlagen"; break;
     case "User Change failed": $tmp = "Benutzer ändern ist fehlgeschlagen"; break;
     case "Registration of new User failed": $tmp = "Registrierung des neuen Benutzers ist fehlgeschlagen"; break;
     case "Database Access failed": $tmp = "Datenbankzugriff ist fehlgeschlagen"; break;
     case "User Deletion failed": $tmp = "Benutzer Löschen ist fehlgeschlagen"; break;
     case "Either your Username or Password are invalid": $tmp = "Entweder Ihr Benutzername oder Passwort ist falsch"; break;
     case "The passwords are not identical": $tmp = "Die Passworte sind nicht identisch"; break;
     case "Please try again": $tmp = "Bitte versuchen Sie es nochmal"; break;
     case "for Enterprise": $tmp = "für Unternehmen"; break;
     case "Please create one": $tmp = "Bitte neu erstellen"; break;
     case "No more Enterprise exist": $tmp = "Es existiert kein weiteres Unternehmen"; break;
     case "No more Contact exist": $tmp = "Es existiert kein weiterer Kontakt"; break;
     case "No more Service exist": $tmp = "Es existiert kein weiterer Dienst"; break;
     case "No more Product exist": $tmp = "Es existiert kein weiteres Produkt"; break;
     case "No more Solution exist": $tmp = "Es existiert keine weitere Lösung"; break;
     case "No more Customer exist": $tmp = "Es existiert kein weiterer Kunde"; break;
     case "No more News exist": $tmp = "Es existiert keine weitere News"; break;
     case "No more Comment exist": $tmp = "Es existiert kein weiterer Kommentar"; break;
     case "No Name specified": $tmp = "Kein Name angegeben"; break;
     case "No Description specified": $tmp = "Keine Beschreibung angegeben"; break;
     case "No Subject specified": $tmp = "Kein Thema angegeben"; break;
     case "No Comment specified": $tmp = "Kein Kommentar angegeben"; break;
     case "No Short Profile specified": $tmp = "Kein Kurzprofil angegeben"; break;
     case "No Profile specified": $tmp = "Kein Unternehmensprofil angegeben"; break;
     case "No News specified": $tmp = "Keine News angegeben"; break;
     case "No Action specified": $tmp = "Kein Aktion angegeben"; break;
     case "An Enterprise with this name already exist": $tmp = "Ein Unternehmen mit diesem Namen existiert bereits"; break;
     case "Unable to copy logofile to logo directory": $tmp = "Logofile konnte nicht in Logo-Verzeichnis kopiert werden"; break;
     case "Unable to change logofile mode": $tmp = "Logofilemode konnte nicht geändert werden"; break;

// User admin
     case "Action": $tmp = "Aktion"; break;
     case "Delete": $tmp = "Löschen"; break;
     case "Create User": $tmp = "Benutzer Erzeugen"; break;
     case "User Creation": $tmp = "Benutzer einrichten"; break;
     case "created": $tmp = "eingerichtet"; break;
     case "User Change": $tmp = "Benutzer ändern"; break;
     case "User Deletion": $tmp = "Benutzer Löschen"; break;
     case "is deleted": $tmp = "wurden gelöscht"; break;

// Categorie admin
     case "Category Administration for": $tmp = "Kategorieadministation für"; break;
     case "Insert a Category": $tmp = "Kategorie hinzufügen"; break;
     case "Rename a Category": $tmp = "Kategorie umbenennen"; break;
     case "Delete a Category": $tmp = "Kategorie löschen"; break;
     case "New Category": $tmp = "Neue Kategorie"; break;
     case "New Category Name": $tmp = "Neuer Kategoriename"; break;
     case "Rename": $tmp = "Umbenennen"; break;
     case "has been added": $tmp = "wurde hinzugefügt"; break;
     case "has been renamed to": $tmp = "wurde umbenannt in"; break;
     case "has been deleted": $tmp = "wurde gelöscht"; break;

// Comment admin
     case "Enterprise by": $tmp = "Unternehmen mit"; break;
     case "All": $tmp = "Alle"; break;
     case "No": $tmp = "Nr"; break;
     case "Author": $tmp = "Autor"; break;
     case "Posted on": $tmp = "Erstellt am"; break;
     case "Status": $tmp = "$phrase"; break;
     case "Erase": $tmp = "Vernichten"; break;

// FAQ admin
     case "Frequently Asked Questions Administration": $tmp = "Administration von oft gestellten Fragen"; break;
     case "New Frequently Asked Question": $tmp = "Neue oft gestellte Frage"; break;
     case "Enter a New Frequently Asked Question": $tmp = "Erstellen einer neuen oft gestellten Frage"; break;
     case "Modify a Frequently Asked Question": $tmp = "Ändern einer oft gestellten Frage"; break;
     case "The following FAQ has been inserted": $tmp = "Die folgende oft gestellten Frage wurde erstellt"; break;
     case "The following FAQ has been modified": $tmp = "Die folgende oft gestellten Frage wurde geändert"; break;
     case "The FAQ has been deleted": $tmp = "Die oft gestellten Frage wurde gelöscht"; break;
     case "Do you really want to delete this FAQ? There is no way for undeletion.": $tmp = "Wollen Sie diese oft gestellten Frage wirklich löschen? Es existiert keine Möglichkeit dies rückgängig zu machen."; break;
     case "Yes, Delete": $tmp = "Ja, Löschen"; break;
     case "No, Just Modify": $tmp = "Nein, nur Ändern"; break;
     case "Create": $tmp = "Erstellen"; break;
     case "Modify": $tmp = "Ändern"; break;

// If no translation available, keep the original phrase
     default: $tmp = "$phrase"; break;
}
?>
