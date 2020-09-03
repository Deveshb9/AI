/*DEVESH BHOGRE PB47 B3-BATCH  AI LAB 5*/
/*Source code of expert system*/
go:-
hypothesis(Disease),
write('I believe that the patient has '),
write(Disease),
nl,
write('See a doctor for a proper medical conclusion.'),nl,
write('TAKE CARE '),
undo;
write('Sorry, the system is unable to identify the disease.'),nl,undo.

/*Hypothesis that should be tested*/
hypothesis(cold) :- cold, !.
hypothesis(flu) :- flu, !.
hypothesis(typhoid) :- typhoid, !.
hypothesis(malaria) :- malaria, !.
hypothesis("chicken pox") :- chicken_pox, !.
hypothesis("whooping cough") :- whooping_cough, !.


/*Hypothesis Identification Rules*/

whooping_cough :-
verify(cough),
verify(sneezing),
verify(runny_nose),
nl,
write('Advices and Suggestions:'),
nl,
write('1: azithromycin'),
nl,
write('2: erythromycin'),
nl,
write('3: clarithromycin'),
nl,!.

chicken_pox :-
verify(rash),
verify(itching),
nl,
write('Advices and Suggestions:'),
nl,
write('1: acyclovir'),
nl,
write('2: Privigen'),
nl,!.

cold :-
verify(headache),
verify(runny_nose),
verify(sneezing),
verify(sore_throat),
nl,
write('Advices and Suggestions:'),
nl,
write('1: Tylenol'),
nl,
write('2: Crocin'),
nl,
write('3: Advil, Motrin'),
nl,!.

flu :-
verify(fever),
verify(headache),
verify(chills),
verify(body_ache),
nl,
write('Advices and Suggestions:'),
nl,
write('1: Relenza'),
nl,
write('2: Rapivab'),
nl,
write('3: Xofluza'),
nl,!.

typhoid :-
verify(headache),
verify(abdominal_pain),
verify(poor_appetite),
verify(fever),
nl,
write('Advices and Suggestions:'),
nl,
write('1: Cipro'),
nl,
write('2: Zithromax'),
nl,
write('3: Ceftriaxone'),
nl,!.

malaria :-
verify(fever),
verify(sweating),
verify(headache),
verify(nausea),
verify(vomiting),
verify(diarrhea),
nl,
write('Advices and Suggestions:'),
nl,
write('1: Malarone'),
nl,
write('2: Mefloquine'),
nl,
write('3: Qualaquin'),
nl,!.

/* how to ask questions */
ask(Question) :-
write('Does the patient have following symptom:'),
write(Question),
write('? '),
read(Response),
nl,
( (Response == yes ; Response == y)
->
assert(yes(Question)) ;
assert(no(Question)), fail).

:- dynamic yes/1,no/1.
/*How to verify something */
verify(S) :-
(yes(S)
->
true ;
(no(S)
->
fail ;
ask(S))).
/* undo all yes/no assertions*/
undo :- retract(yes(_)),fail.
undo :- retract(no(_)),fail.
undo.