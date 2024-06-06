# Королівська балда

## Опис гри

Грає людина проти комп'ютера. Починає комп'ютер. В середині поля розміром 5х5 клітин пишеться слово з п'яти букв. Людина повинна придумати нове слово, що складається з Знаходяться на поле букв і обов'язково однієї нової (додається на поле) літери.
На рівні інтерфейсу це виглядає так. Комп'ютер дозволяє людині поставити букву в будь-яку вільну клітину, потім людина вказує, яким чином нове слово слід читати. Слова можуть утворюватися з букв, розташованих послідовно в будь-якому напрямку від клітини до клітини вгору, вниз, вліво або вправо, але не по діагоналі і без самоперетинів.

Чим довше нове слово, тим більше очок за нього дається (по очку за букву). Потім хід переходить до суперника. Однакові слова не допускаються. Якщо гравець не в змозі придумати чергове слово (це відноситься як до людини, так і до комп'ютера), він може пропустити хід.

Гра завершується при заповненні останньої клітини поля або при виникненні ситуації, коли жоден з гравців не може зробити хід. Виграє той, у кого більше очок.
Зазвичай в балді допускаються тільки іменники в називному відмінку та однині. У програмі повинна бути передбачена функція поповнення словника: якщо людина складає слово, невідоме комп'ютера, комп'ютер додає його в свою базу даних. Для гри можна використовувати просту «жадібну стратегію»: на черговому ході вибирається слово, дає найбільший приріст очок (навіть якщо це загрожує втраченими можливостями в майбутньому)."

## Корисні посилання

- [Балда](https://ru.wikipedia.org/wiki/%D0%91%D0%B0%D0%BB%D0%B4%D0%B0_(%D0%B8%D0%B3%D1%80%D0%B0)) на Вікіпедії (російською)

- [Балда](https://balda.org.ua/) онлайн

## TODO LIST

- [x] bot make move: randomize position

- [x] easy difficulty: skip sometime move
- [x] hard difficulty: see all moves then do move

- [x] leaderboards

- [x] 2 players gameplay

- [ ] easter egg zip bomb

- [ ] funny easter eggs