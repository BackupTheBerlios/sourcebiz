<?php
switch($phrase) {

// Top strip
     case "Home": $tmp = "P&aacute;gina Principal"; break;
     case "About us":  $tmp = "Nosotros"; break;
     case "Partners": $tmp = "Colaboradores"; break;
     case "Contact": $tmp = "Contacto"; break;

     case "Logged in": $tmp = "Usuario"; break;
     case "Expires": $tmp = "Expira"; break;
     case "Not Logged in": $tmp = "No autentificado"; break;

// Top title
     case "Open Source Software Announcement &amp; Retrieval":  $tmp = "Anuncio y B&uacute;squeda de Aplicaciones de C&oacute;digo Abierto"; break;

// Menue Bar
     case "Recent Apps": $tmp = "Novedades"; break;
     case "Q&amp;A": $tmp = "P&amp;R"; break;
     case "Login": $tmp = "$phrase"; break;
     case "Logout": $tmp = "$phrase"; break;
     case "New User": $tmp = "Usuario Nuevo"; break;
     case "Forgot Password": $tmp = "Recordar Contrase&ntilde;a"; break;
     case "Change User": $tmp = "Modificar Registro"; break;
     case "Users": $tmp = "Usuarios"; break;

     case "Apps Index": $tmp = "&Iacute;ndice"; break;
     case "New Apps": $tmp = "Introducir"; break;
     case "Update Apps": $tmp = "Actualizar"; break;
     case "Pending Apps": $tmp = "Validar"; break;
     case "Deleted Apps": $tmp = "Borrar";break;
     case "Modified Apps": $tmp = "Modified Apps";break;

     case "Newsletter": $tmp = "Lista de Noticias"; break;
     case "Backend": $tmp = "$phrase"; break;
     case "Statistics": $tmp = "Estad&iacute;sticas"; break;

     case "Administration": $tmp = "Administraci&oacute;n"; break;
     case "Sections": $tmp = "Secciones"; break;
     case "Categories": $tmp = "Categor&iacute;as"; break;
     case "Authors": $tmp = "Autores"; break;
     case "Licenses": $tmp = "Licencias"; break;
     case "Check Date": $tmp = "Check Date"; break;

     case "Search": $tmp = "Buscar"; break;
     case "Language": $tmp = "Idioma"; break;
     case "Go": $tmp = "Cambiar"; break;

// Languages
	 case "English": $tmp = "Ingl&eacute;s"; break;
	 case "German": $tmp = "Alem&aacute;n"; break;
	 case "Spanish": $tmp = "Espa&ntilde;ol"; break;

// sorted by
	 case "sorted by": $tmp = "ordenado por"; break;
	 case "Date": $tmp = "Fecha"; break;
	 case "Importance": $tmp = "Importancia"; break;
	 case "Urgency": $tmp = "Urgencia"; break;
	 case "Name": $tmp = "Nombre"; break;
// FAQ
     case "Frequently Asked Questions": $tmp = "Preguntas Frecuentes"; break;
     case "Question": $tmp = "Pregunta"; break;
     case "Answer": $tmp = "Respuesta"; break;

// Apps update
     case "Comment": $tmp = "Comentario"; break;
     case "Review": $tmp = "Revisar"; break;
     case "Update": $tmp = "Actualizar"; break;

// Apps not yet reviewed

     case "Waiting for Review by an Editor": $tmp = "Esperando revisi&oacute;n por parte"; break;

// Apps by identifier
     case "Application": $tmp = "La aplicaci&oacute;n"; break;
     case "has not yet been reviewed by a $GLOBALS[sys_name] Editor.<br> Please, be patient. It will be surely done in the next time.": $tmp = "no ha sido todav&iacute;a revisada por $GLOBALS[sys_name].<br> Por favor, sea paciente. Seguro que ser&aacute; revisada en poco tiempo."; break;
     case "is modified": $tmp = "$phrase"; break;
     case "is deleted": $tmp = "$phrase"; break;


// User registration
     case "Register as a new User": $tmp = "Registrarse como usuario nuevo"; break;
     case "Username": $tmp = "Nombre de usuario"; break;
     case "Password": $tmp = "Contrase&ntilde;a"; break;
     case "Confirm Password": $tmp = "Confirmar Contrase&ntilde;a"; break;
     case "Realname": $tmp = "Nombre real"; break;
     case "Register": $tmp = "Registrarse"; break;
     case "User Registration": $tmp = "Registro de usuario"; break;
     case "Congratulations": $tmp = "Enhorabuena"; break;
     case "You have registered on $GLOBALS[sys_name]": $tmp = "Se ha registrado en $GLOBALS[sys_name]"; break;
     case "Your new username is": $tmp = "Su nombre de usuario es"; break;
     case "You are now being sent a confirmation email to verify your email address": $tmp = "Se est&aacute; enviando un correo-e de confirmaci&oacute;n para verificar su direcci&oacute;n de correo electr&oacute;nica"; break;
     case "Visiting the link sent to you in this email will activate your account": $tmp = "Si visita el enlace que se le env&iacute;a en el correo electr&oacute;nico, podr&aacute; activar su cuenta"; break;
     case "Thank you for registering on the $GLOBALS[sys_name] Site. In order": $tmp = "Gracias por registrarse en Sourcewell. Para"; break;
     case "to complete your registration, visit the following URL": $tmp = "completar su registro, visite la siguiente URL"; break;
     case "Enjoy the site": $tmp = "Esperamos que disfrute de $GLOBALS[sys_name]"; break;
     case " -- the $GLOBALS[sys_name] crew": $tmp = " -- el equipo de $GLOBALS[sys_name]"; break;
     case "Verification of Registration": $tmp = "Verificaci&oacute;n del Registro"; break;
     case "Your account is now activated. Please login": $tmp = "Su cuenta ha sido activada. Por favor, haga login"; break;

// Forget password / Remind me
     case "Register as a new User": $tmp = "Registrarse como un usuario nuevo"; break;
     case "Remind me": $tmp = "Recordar"; break;
     case "Your Username and Password for $GLOBALS[sys_name] is": $tmp = "Su nombre de usuario y contrase&ntilde;a para $GLOBALS[sys_name] es"; break;
     case "Please keep this e-mail for further reference": $tmp = "Por favor, guarde debidamente este mensaje de correo-e para posteriores referencias"; break;
     case "You will get your Password by e-mail in a couple of minutes": $tmp = "Recibir&aacute; su contrase&ntilde;a por correo-e en unos minutos"; break;

// Change User Parameters
     case "Change User Parameters": $tmp = "Cambiar los datos de usuario"; break;
     case "Remind me": $tmp = "Recordar"; break;
     case "Modification": $tmp = "Modificado"; break;
     case "Creation": $tmp = "Creado"; break;
     case "Permission": $tmp = "Derechos"; break;
     case "Change": $tmp = "Cambiar"; break;
     case "Password and/or E-Mail Address of": $tmp = "La contrase&ntilde;a y/o la direcci&oacute;n de correo-e de"; break;
     case "is changed": $tmp = "ha cambiado"; break;

// Apps Index
     case "Section": $tmp = "Secci&oacute;n"; break;
     case "Category": $tmp = "Categor&iacute;a"; break;

// Apps by category
     case "Homepage": $tmp = "P&aacute;gina Principal"; break;
     case "Download": $tmp = "Descargas"; break;
     case "Changelog": $tmp = "Log de cambios"; break;
     case "Comments": $tmp = "Comentarios"; break;
     case "Type": $tmp = "Tipo"; break;
     case "Updated": $tmp = "Actualizada"; break;
     case "Created": $tmp = "Creada"; break;
     case "Stable": $tmp = "Estable"; break;
     case "Development": $tmp = "Desarrollo"; break;
     case "License": $tmp = "Licencia"; break;

// New Apps
     case "New Application": $tmp = "Nueva Aplicaci&oacute;n"; break;
     case "Application Name": $tmp = "Nombre de la Aplicaci&oacute;n"; break;
     case "Insert": $tmp = "Insertar"; break;

// Insert Apps
     case "Insert Application": $tmp = "Insertar Aplicaciones"; break;
     case "Stable Version": $tmp = "Versi&oacute;n estable"; break;
     case "Development Version": $tmp = "Versi&oacute;n de desarrollo"; break;
     case "Section/Category": $tmp = "Secci&oacute;n/Categor&iacute;a"; break;
     case "Red Hat Package": $tmp = "Paquete Red Hat"; break;
     case "Debian Package": $tmp = "Paquete Debian"; break;
     case "Slackware Package": $tmp = "Paquete Slackware"; break;
     case "CVS Tree": $tmp = "CVS Tree"; break;
     case "Screenshots": $tmp = "Screenshots"; break;
     case "Mailing List Archive": $tmp = "Mailing List Archive"; break;
     case "Description": $tmp = "Descripci&oacute;n"; break;
     case "Author": $tmp = "Autor"; break;
     case "Depends on": $tmp = "Depende de"; break;

// Update Apps
     case "Update Application": $tmp = "Modificar Aplicaci&oacute;n"; break;
     case "Application ID": $tmp = "ID de la Aplicaci&oacute;n"; break;
     case "Announcements": $tmp = "Avisos"; break;

// Comment
     case "Your Comment about": $tmp = "Tu comentario a"; break;
     case "Subject": $tmp = "Tema"; break;
     case "Comment": $tmp = "Comentario"; break;
     case "Send": $tmp = "Enviar"; break;

// Login
     case "Welcome to $GLOBALS[sys_name]": $tmp = "Bienvenido a $GLOBALS[sys_name]"; break;
     case "You do not have the permission to login": $tmp = "No tiene permiso para hacer login"; break;
     case "You are logged in as": $tmp = "Se ha autentificado como"; break;
     case "with": $tmp = "con permiso(s) de"; break;
     case "permission": $tmp = ""; break;
     case "Your authentication is valid until": $tmp = "Su autentificaci&oacute;n es v&aacute;lida hasta el"; break;

// Logout
     case "You have been logged in as": $tmp = "Se autentific&oacute; como"; break;
     case "Your authentication was valid until": $tmp = "Su autentificaci&oacute;n era v&aacute;lida hasta el"; break;
     case "This is all over now. You have been logged out": $tmp = "Ya ha terminado. Su autentificaci&oacute;n ha sido dada de baja"; break;

// User admin
     case "Action": $tmp = "Acci&oacute;n"; break;
     case "Delete": $tmp = "Borrar"; break;
     case "Create User": $tmp = "Crear Usuario"; break;
     case "User Creation": $tmp = "Creaci&oacute;n de Usuario"; break;
     case "created": $tmp = "ha sido creado"; break;
     case "User Change": $tmp = "Cambiar Usuario"; break;
     case "User Deletion": $tmp = "Borrar Usuario"; break;
     case "is deleted": $tmp = "ha sido borrado"; break;

// Section admin
     case "Section Administration": $tmp = "Administraci&oacute;n de Secciones"; break;
     case "Insert a Section": $tmp = "Introducir Secci&oacute;n"; break;
     case "Rename a Section": $tmp = "Renombrar una Secci&oacute;n"; break;
     case "Delete a Section": $tmp = "Borrar una Secci&oacute;n"; break;
     case "New Section": $tmp = "Secci&oacute;n Nueva"; break;
     case "New Section Name": $tmp = "Nombre de la nueva Secci&oacute;n"; break;
     case "Section": $tmp = "Secci&oacute;n"; break;
     case "Rename": $tmp = "Renombrar"; break;

// Category admin
     case "Category Administration": $tmp = "Administraci&oacute;n de Categor&iacute;as"; break;
     case "Insert a Category": $tmp = "A&ntilde;adir Categor&iacute;a"; break;
     case "Rename a Category": $tmp = "Renombrar una Categor&iacute;a"; break;
     case "Delete a Category": $tmp = "Borrar una Categor&iacute;a"; break;
     case "New Category": $tmp = "Categor&iacute;a Nueva"; break;
     case "New Category Name": $tmp = "Nombre de la nueva Categor&iacute;a"; break;
     case "Category": $tmp = "Categor&iacute;a"; break;

// License admin
     case "License Administration": $tmp = "Administraci&oacute;n de Licencias"; break;
     case "Insert a License": $tmp = "Introducir una Licencia"; break;
     case "Rename a License": $tmp = "Renombrar una Licencia"; break;
     case "Change a License URL": $tmp = "Cambiar la URL de una Licencia"; break;
     case "Delete a License": $tmp = "Borrar una Licencia"; break;
     case "New License": $tmp = "Nueva Licencia"; break;
     case "License URL": $tmp = "URL de la Licencia"; break;
     case "New License Name": $tmp = "Nombre de la Nueva Licencia"; break;
     case "New License URL": $tmp = "URL de la Nueva Licencia"; break;
     case "License": $tmp = "Licencia"; break;

// Announcements
    case "by": $tmp = "por"; break;
    case "on": $tmp = "el"; break;
	case "hits": $tmp = "&quot;hits&quot;"; break;

// Time-based Navigation
    case "Day": $tmp = "D&iacute;a"; break;
    case "Today": $tmp = "Hoy"; break;
    case "Week": $tmp = "Semana"; break;

// Search
    case "No Application found": $tmp = "No se ha encontrado ninguna aplicaci&oacute;n"; break;

// Apps by user
     case "No Apps of User exist": $tmp = "No existen aplicaciones del usuario"; break;

// Pending Apps
     case "Apps of User": $tmp = "Aplicaciones del usuario"; break;
     case "No pending Apps exist": $tmp = "No hay aplicaciones por validar"; break;

// Deleted or modified apps
     case "Is deleted": $tmp = "Ha sido borrada"; break;
     case "Is modified": $tmp = "Ha sido modificada"; break;
     case "No deleted Apps exist": $tmp = "No hay aplicaciones borradas"; break;
     case "No modified Apps exist": $tmp = "No hay aplicaciones modificadas"; break;

// Users
    case "No": $tmp = "Nr"; break;
    case "All": $tmp = "Todos"; break;

// Developers
    case "Names": $tmp = "Nombres"; break;
    case "Unknown": $tmp = "Desconocido"; break;

// Licences
     case "Apps": $tmp = "Apl."; break;

// Check Date
     case "All dates are consistent": $tmp = "Todas las fechas son consistentes"; break;

// Newsletter
     case "Subscribe Newsletter": $tmp = "Suscribirse a la Lista de Noticias"; break;
     case "Subscribe": $tmp = "Suscribirse"; break;
     case "Send newsletter": $tmp = "Mandar Lista Noticias"; break;
     case "Newsletter was sent at ": $tmp = "La Lista de Noticias fue enviada a "; break;
     case "You have subscribed to $GLOBALS[sys_name] Newsletter": $tmp = "Se ha abonado a la Lista de Noticias de $GLOBALS[sys_name]"; break;
     case "Daily Newsletter": $tmp = "Lista de Noticias Diaria"; break;
     case "Weekly Newsletter": $tmp = "Lista de Noticias Semanal"; break;
     case "daily": $tmp = "diariamente"; break;
     case "weekly": $tmp = "semanalmente"; break;

// Statistics
	 case "$GLOBALS[sys_name] Statistics": $tmp = "Estad&iacute;sticas de $GLOBALS[sys_name]"; break;
	 case "General $GLOBALS[sys_name] Statistics": $tmp = "Estad&iacute;sticas Generales de $GLOBALS[sys_name]"; break;
	 case "Apps by Importance": $tmp = "Aplicaciones por Importancia"; break;
	 case "Apps by Hits": $tmp = "Aplicaciones por &quot;Hits&quot;"; break;
	 case "Apps by Homepage Visits": $tmp = "Aplicaciones por Visitas a la P&aacute;gina Principal"; break;
	 case "Apps by Downloads": $tmp = "Aplicaciones por Descargas"; break;
	 case "Top downloaded RPM Packages": $tmp = "Top de Paquetes Red Hat descargados"; break;
	 case "Top downloaded Debian Packages": $tmp = "Top de Paquetes Debian descargados"; break;
	 case "Top downloaded Slackware Packages": $tmp = "Top de Paquetes Slackware descargados"; break;
	 case "Apps and Downloads by Urgency": $tmp = "Aplicaciones y Descargas por Urgencia"; break;
	 case "Apps and Downloads by Version Types": $tmp = "Aplicaciones y Descargas por Tipo de Versi&oacute;n"; break;
	 case "Apps and Importance by Sections": $tmp = "Aplicaciones e Importancia por Secciones"; break;
	 case "Apps by Categories": $tmp = "Aplicaciones por Categor&iacute;a"; break;
	 case "Apps by Version Numbers": $tmp = "Aplicaciones por N&uacute;mero de Versi&oacute;n"; break;
	 case "Apps and Downloads by Package Formats": $tmp = "Aplicaciones y Descargas por Formato de Paquete"; break;
	 case "Importance by Licenses": $tmp = "Importancia por Licencias"; break;
	 case "Importance by Email Domains": $tmp = "Importancia por Dominio de Correo-e"; break;
	 case "Apps by Email Domains": $tmp = "Aplicaciones por Dominio de Correo-e"; break;
	 case "Apps by Sections and Email Domains": $tmp = "Aplicaciones por Secciones y Domnio de Correo-e"; break;
	 case "Apps by Licenses": $tmp = "Aplicaciones por Licencia"; break;
	 case "Apps by Licenses and Email Domains": $tmp = "Aplicaciones por Licencia y Dominio de Correo-e"; break;

// General Statistics
	 case "Number of Applications in $GLOBALS[sys_name]": $tmp = "N&uacute;mero de Aplicaciones en $GLOBALS[sys_name]"; break;
	 case "Total Number of Insertions and Modifications": $tmp = "N&uacute;mero de Introducciones y Modificaciones"; break;
	 case "Number of Insertions and Modifications during the last week": $tmp = "N&uacute;mero de Introducciones y Modificaciones en la &uacute;ltima semana"; break;
	 case "Number of pending Applications": $tmp = "N&uacute;mero de aplicaciones pendientes de validaci&oacute;n"; break;
	 case "Number of $GLOBALS[sys_name] authorised Users": $tmp = "N&uacute;mero de Usuarios Autorizados de $GLOBALS[sys_name]"; break;
	 case "Number of Comments on Applications": $tmp = "N&uacute;mero de Comentarios a Aplicaciones"; break;
	 case "Number of Licenses listed in $GLOBALS[sys_name]": $tmp = "N&uacute;mero de Licencias listadas en $GLOBALS[sys_name]"; break;
	 case "Number of $GLOBALS[sys_name] Sections": $tmp = "N&uacute;mero de Secciones en $GLOBALS[sys_name]"; break;
	 case "Number of $GLOBALS[sys_name] Categories": $tmp = "N&uacute;mero de Categor&iacute;as en $GLOBALS[sys_name]"; break;
	 case "Total Number of Hits on Applications": $tmp = "N&uacute;mero total de &quot;Hits&quot; sobre Aplicaciones"; break;
	 case "Number of redirected Homepages": $tmp = "N&uacute;mero de P&aacute;ginas Principales redireccionadas"; break;
	 case "Number of Downloads": $tmp = "N&uacute;mero de Descargas"; break;
	 case "Number of redirected Changelogs": $tmp = "N&uacute;mero de Log de Cambios redireccionados"; break;
	 case "Number of redirected CVSs": $tmp = "N&uacute;mero de CVSs redireccionados"; break;
	 case "Number of redirected Screenshots": $tmp = "N&uacute;mero de Capturas de Pantallas redireccionadas"; break;
	 case "Number of redirected Mailing Lists Archives": $tmp = "N&uacute;mero de Archivos de Listas de Correo-e redireccionadas"; break;
	 case "SourceWell Version": $tmp = "Versi&oacute;n de SourceWell"; break;

	 case "High Urgency": $tmp = "$phrase"; break;
	 case "Medium Urgency": $tmp = "$phrase"; break;
	 case "Low Urgency": $tmp = "$phrase"; break;
	 case "Stable Version": $tmp = "$phrase"; break;
	 case "Development Version": $tmp = "$phrase"; break;
	 case "Version Number": $tmp = "$phrase"; break;
	 case "Tarballs": $tmp = "$phrase"; break;
	 case "Red Hat Packages": $tmp = "$phrase"; break;
	 case "Debian Packages": $tmp = "$phrase"; break;
	 case "Slackware Packages": $tmp = "$phrase"; break;
	 case "Applications listed by their Importance": $tmp = "Aplicaciones por orden de Importancia"; break;
	 case "Applications listed by Number of Tarball-Downloads": $tmp = "Aplicaciones ordenadas por N&uacute;mero de Descargas de &quot;Tarballs&quot;"; break;
	 case "Applications listed by Number of Hits": $tmp = "Aplicaciones ordenadas por N&uacute;mero de &quot;Hits&quot;"; break;
	 case "Applications listed by Homepage Visits": $tmp = "Aplicaciones ordenadas por Visitas a la P&aacute;gina Principal"; break;
	 case "Top downloaded Red Hat Packages": $tmp = "Top de Paquetes Red Hat descargados"; break;
	 case "Top downloaded Debian Packages": $tmp = "Top de Paquetes Debian descargados"; break;
	 case "Top downloaded Slackware Packages": $tmp = "Top de Paquetes Slackware descargados"; break;
	 case "Application Importance listed by Sections": $tmp = "Importancia de las Aplicaciones por Secciones"; break;
	 case "Applications listed by Sections": $tmp = "Aplicaciones por Secciones"; break;
	 case "Applications listed by Categories": $tmp = "Aplicaciones por Categor&iacute;as"; break;
	 case "Applications listed by Licenses": $tmp = "Aplicaciones por Licencia"; break;
	 case "Availability of downloadable Packet Formats": $tmp = "Disponibilidad de Formatos de Paquete descargables"; break;
	 case "Downloads listed by Packet Formats": $tmp = "Descargas ordenadas por Formato de Paquete"; break;
	 case "Applications listed by Urgency": $tmp = "Aplicaciones por Urgencia"; break;
	 case "Downloads listed by Urgency": $tmp = "Descargas por Urgencia"; break;
	 case "Applications listed by Version Numbers": $tmp = "Aplicaciones por N&uacute;mero de Versi&oacute;n"; break;
	 case "Applications listed by Licenses": $tmp = "Aplicaciones por Licencia"; break;
	 case "Applications listed by Version Type": $tmp = "Aplicaciones por Tipo de Versi&oacute;n"; break;
	 case "Downloads listed by Version Type": $tmp = "Descargas por Tipo de Versi&oacute;n"; break;
	 case "Application Importance listed by Licenses": $tmp = "Importancia de las Aplicaciones ordenada por Licencias"; break;
	 case "Application Importance listed by Developer's Email Domains": $tmp = "Importancia de las Aplicaciones seg&uacute;n el Dominio de Correo-e del Desarrollador"; break;
	 case "Applications listed by Developer's Email Domain": $tmp = "Aplicaciones por Dominio de Correo-e del Desarrollador"; break;
	 case "Applications listed by Sections and Developer's Email Domain": $tmp = "Aplicaciones por Secciones y por Dominio de Correo-e del Desarrollador"; break;
	 case "Applications listed by Licenses and Developer's Email Domain": $tmp = "Aplicaciones por Licencias y por Dominio de Correo-e del Desarrollador"; break;

// Errors
     case "Access denied": $tmp = "Acceso denegado"; break;
     case "Error": $tmp = "Error"; break;
     case "does not exist": $tmp = "no existe"; break;
     case "Change User Parameters failed": $tmp = "El cambio de los par&aacute;metros de usuario ha fallado"; break;
     case "No Application ID specified": $tmp = "No se ha especificado ninguna ID"; break;
     case "No Application Name specified": $tmp = "No se ha especificado un nombre de una aplicaci&oacute;n"; break;
     case "Please select": $tmp = "Por favor, escoja"; break;
     case "Parameter missing": $tmp = "Falta par&aacute;metro"; break;
     case "and": $tmp = "y"; break;
     case "User": $tmp = "Usuario"; break;
     case "already exists": $tmp = "ya existe"; break;
     case "Please select a different Username": $tmp = "Por favor, escoja otro nombre de usuario"; break;
     case "Please enter": $tmp = "Por favor, introduzca:"; break;
     case "Either your Username or E-Mail Address is unknown": $tmp = "Esta combinaci&oacute;n nombre de usuario - direcci&oacute;n de correo-e es desconocida."; break;
     case "Please try again": $tmp = "Por favor, int&eacute;ntelo otra vez"; break;
     case "If you are not yet a registered User, please select": $tmp = "Si no es un usuario registrado, por favor, escoja"; break;
     case "Verification of Registration failed": $tmp = "Ha fallado la verificaci&oacute;n del registro"; break;
     case "User Change failed": $tmp = "Cambio de usuario ha fallado"; break;
     case "Registration of new User failed": $tmp = "Ha fallado el registro de un nuevo usuario"; break;
     case "Database Access failed": $tmp = "Fallo en el acceso a la base de datos"; break;
     case "User Deletion failed": $tmp = "Ha fallado el borrado de usuario"; break;
     case "No more Apps for this day": $tmp = "No hay m&aacute;s aplicaciones para este d&iacute;a"; break;
     case "Either your Username or Password are invalid": $tmp = "La combinaci&oacute;n nombre de usuario - contrase&ntilde;a introducidas son inv&aacute;lidas"; break;
     case "The passwords are not identical": $tmp = "Las contrase&ntilde;as no son id&eacute;nticas"; break;
     case "Please try again": $tmp = "Por favor, int&eacute;ntelo otra vez"; break;
     case "License description is not available": $tmp = "La descripci&oacute;n de la licencia no est&aacute; disponible"; break;

// If no translation available, keep the original phrase
     default: $tmp = "$phrase"; break;
}
?>