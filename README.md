# UEEditorRichPresence

Plugin Editor per Unreal Engine che fornisce una Rich Presence (es. integrazione con Discord) basata sullo stato dell'Editor.

## Descrizione

Questo plugin tiene aggiornata la Rich Presence esterna (ad esempio Discord) con informazioni sull'Editor di Unreal Engine: progetto aperto, mappa corrente, stato Play-In-Editor e altre informazioni utili mentre si lavora.

## Funzionalità

- Avvia/ferma l'integrazione con l'SDK di Rich Presence.
- Aggiorna automaticamente lo stato in base alla mappa aperta e allo stato di Play-In-Editor.
- Impostazioni configurabili dall'Editor (Application Id, immagini, testo mostrato).

## Installazione

1. Copia la cartella del plugin nella cartella `Plugins` del tuo progetto Unreal (o mantienila come plugin nel repository del progetto).
2. Compila il progetto Unreal (Editor) in modo che il modulo venga riconosciuto.
3. Se usi uno SDK nativo (es. Discord Game SDK), posiziona la libreria nativa (DLL / SO) nella cartella appropriata o configura il percorso previsto dal build script.

Per dettagli sulla configurazione nativa, consulta `Source/UEEditorRichPresence/UEEditorRichPresence.Build.cs`.

## Configurazione

Dopo aver installato il plugin, apri le impostazioni dell'Editor e cerca la sezione "Editor Rich Presence". Le impostazioni principali includono:

- `Discord Application Id` — l'ID dell'app Discord da usare per la Rich Presence.
- Opzioni per mostrare: nome del progetto, nome della mappa, durata della sessione, immagini personalizzate.

Le impostazioni sono definite in: `Source/UEEditorRichPresence/Public/UEERPSettings.h`.

## Come funziona (breve panoramica)

- Il modulo principale è `FUEEditorRichPresenceModule` definito in `Source/UEEditorRichPresence/UEEditorRichPresenceModule.h` e implementato in `.cpp`.
- Un sottosistema (`UUEERPSubsystem`) ascolta gli eventi dell'Editor (apertura mappa, cambio stato PIE, ecc.) e richiede gli aggiornamenti di presenza.
- L'interazione con l'SDK esterno è incapsulata in `FDiscordWrapper` (`Source/UEEditorRichPresence/Private/Discord/DiscordWrapper.*`).

## Sviluppo

- Il modulo è configurato come modulo Editor nel file `Source/UEEditorRichPresence/UEEditorRichPresence.Build.cs`.
- Punti di estensione utili per sviluppo e debug:
	- `Source/UEEditorRichPresence/Private/UEERPSubsystem.cpp` — logica di eventi e trigger di aggiornamento presenza.
	- `Source/UEEditorRichPresence/Private/Discord/DiscordWrapper.cpp` — init/cleanup e chiamate allo SDK (contiene i TODO per completare integrazione).

## Debug e log

- Il plugin usa i log di Unreal Engine (ad es. `UE_LOG`) per riportare eventi e problemi di inizializzazione.
- Se il plugin non si avvia, verifica:
	- presenza e percorso della libreria nativa (DLL/SO)
	- correttezza del `Discord Application Id`
	- permessi e blocchi da antivirus/sandbox

## File principali

- `UEEditorRichPresence.uplugin` — metadata del plugin.
- `Source/UEEditorRichPresence/UEEditorRichPresence.Build.cs` — regole di build del modulo.
- `Source/UEEditorRichPresence/UEEditorRichPresenceModule.*` — entrypoint del modulo.
- `Source/UEEditorRichPresence/Public/UEERPSettings.h` — impostazioni esposte nell'Editor.
- `Source/UEEditorRichPresence/Private/UEERPSubsystem.*` — gestione eventi Editor e orchestrazione presenza.
- `Source/UEEditorRichPresence/Private/Discord/DiscordWrapper.*` — wrapper verso l'SDK esterno.

## Esempio rapido: prova locale

1. Posiziona il plugin nella cartella `Plugins` del progetto Unreal.
2. Apri il progetto in Unreal Editor e abilita il plugin tramite la finestra Plugin.
3. Imposta l'`Application Id` nelle impostazioni del plugin.
4. Avvia una sessione Play-In-Editor e verifica che la Rich Presence venga aggiornata (controlla i log dell'Editor).

## Licenza

Specifica qui la licenza del progetto (ad es. MIT, GPLv3, ecc.). Se non vuoi includerne una, aggiungi una nota esplicita.

## Contatti

Per domande o contributi, apri una issue o una pull request nel repository: `https://github.com/Papin-Network/UEEditorRichPresence`.

---

Se vuoi, posso aggiungere anche un file `CONTRIBUTING.md` e un esempio di `ThirdParty` per il posizionamento delle librerie native.

