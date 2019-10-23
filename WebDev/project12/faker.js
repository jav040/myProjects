var faker = require('faker');
for(var i = 0; i < 10; i++)
{
  console.log(faker.fake("{{random.word}} {{random.word}} {{random.word}} - ${{finance.amount}}"));

}
