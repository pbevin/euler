#include "euler.h"

struct card {
  int rank;
  char suit;
};
struct hand {
  struct card card[5];
};

static void
readcard(struct card *card, const char *buf) {
  card->suit = buf[1];
  switch (buf[0]) {
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    card->rank = buf[0] - '0'; break;
  case 'T':
    card->rank = 10; break;
  case 'J':
    card->rank = 11; break;
  case 'Q':
    card->rank = 12; break;
  case 'K':
    card->rank = 13; break;
  case 'A':
    card->rank = 14; break;
  default:
    fprintf(stderr, "Bad card %c%c\n", buf[0], buf[1]);
  }
}

static void
readhand(struct hand *p, const char *buf) {
  for (int i = 0; i < 5; i++) {
    readcard(&p->card[i], buf + i * 3);
  }
}

static void
readhands(struct hand *p1, struct hand *p2, const char *buf) {
  readhand(p1, buf);
  readhand(p2, buf+15);
}

static int rankcmp(const void *a, const void *b) {
  const int *aa = a;
  const int *bb = b;
  return *aa - *bb;
}

static void ranksort(struct hand *hand, int *val) {
  for (int i = 0; i < 5; i++) {
    val[i] = hand->card[i].rank;
  }
  qsort(val, 5, sizeof(int), rankcmp);
}

static int pokstr(struct hand *hand) {
  int val[5];
  ranksort(hand, val);

  if (val[0] + 1 == val[1] &&
      val[0] + 2 == val[2] &&
      val[0] + 3 == val[3] &&
      val[0] + 4 == val[4]) {
    return val[4];
  }
  return 0;
}

static int hicard(struct hand *hand) {
  int val[5];
  ranksort(hand, val);
  return val[4];
}

int chk4kind(struct hand *hand) {
  int val[5];
  ranksort(hand, val);
  if (
      (val[0] == val[1] || val[3] == val[4]) &&
      val[1] == val[2] &&
      val[2] == val[3]
  ) {
    return val[1];
  } else {
    return 0;
  }
}

static int
chkfh(struct hand *hand) {
  int val[5];
  ranksort(hand, val);

  if (val[0] == val[1] && val[1] == val[2] && val[3] == val[4]) {
    return val[0];
  } else if (val[0] == val[1] && val[2] == val[3] && val[3] == val[4]) {
    return val[4];
  } else {
    return 0;
  }
}

static int chk3kind(struct hand *hand) {
  int val[5];
  ranksort(hand, val);

  if (val[0] == val[1] && val[1] == val[2]) {
    return val[0];
  } else if (val[1] == val[2] && val[2] == val[3]) {
    return val[1];
  } else if (val[2] == val[3] && val[3] == val[4]) {
    return val[2];
  } else {
    return 0;
  }
}

static int chk2pair(struct hand *hand) {
  int val[5];
  ranksort(hand, val);

  if (val[0] == val[1] && val[2] == val[3]) {
    return val[2];
  } else if (val[0] == val[1] && val[3] == val[4]) {
    return val[3];
  } else if (val[1] == val[2] && val[3] == val[4]) {
    return val[3];
  } else {
    return 0;
  }
}

static int chkpair(struct hand *hand) {
  int val[5];
  ranksort(hand, val);

  if (val[0] == val[1]) {
    return val[0];
  } else if (val[1] == val[2]) {
    return val[1];
  } else if (val[2] == val[3]) {
    return val[2];
  } else if (val[3] == val[4]) {
    return val[3];
  } else {
    return 0;
  }
}

/*
 * 1000 = royal flush
 * 9xx = straight flush (xx = rank of high card)
 * 8xx = 4 of a kind (xx = rank)
 * 7xx = full house (xx = rank of 3some)
 * 6xx = flush (xx = rank of high card)
 * 5xx = straight (xx = rank of high card)
 * 4xx = 3 of a kind (xx = rank)
 * 3xx = 2 pairs (xx = rank of high pair)
 * 2xx = 1 pair (xx = rank of pair)
 * 1xx = high card (xx = rank of card)
 */
static int
evalhand(struct hand *hand) {
  int isflush = (
      hand->card[0].suit == hand->card[1].suit &&
      hand->card[0].suit == hand->card[2].suit &&
      hand->card[0].suit == hand->card[3].suit &&
      hand->card[0].suit == hand->card[4].suit
  );
  int straight = pokstr(hand);
  int highcard = hicard(hand);
  int fourofkind = chk4kind(hand);
  int fullhouse = chkfh(hand);
  int threeofkind = chk3kind(hand);
  int twopairs = chk2pair(hand);
  int pair = chkpair(hand);

  if (isflush && straight == 14) {
    return 1000;
  } else if (isflush && straight) {
    return 900 + straight;
  } else if (fourofkind) {
    return 800 + fourofkind;
  } else if (fullhouse) {
    return 700 + fullhouse;
  } else if (isflush) {
    return 600 + highcard;
  } else if (straight) {
    return 500 + straight;
  } else if (threeofkind) {
    return 400 + threeofkind;
  } else if (twopairs) {
    return 300 + twopairs;
  } else if (pair) {
    return 200 + pair;
  } else {
    return highcard + 100;;
  }
}

static void
chkeval(const char *buf, int expscore) {
  struct hand p;
  readhand(&p, buf);
  int score = evalhand(&p);
  if (score != expscore) {
    fprintf(stderr, "%s: expected %d, got %d\n", buf, expscore, score);
  }
}


static void
poktest() {
  chkeval("2H 4S 5C 7S TC", 110);
  chkeval("5S 2H JC AD 5D", 205);
  chkeval("2S 3S 2H 3C 5H", 303);
  chkeval("5S 2C JH 5H 5C", 405);
  chkeval("7S 4H 5C 6C 3D", 507);
  chkeval("3S 7S 5S JS TS", 611);
  chkeval("4S 4H 4C 8C 8S", 704);
  chkeval("8S 8H 8C 4C 4S", 708);
  chkeval("5C 5D 5H 5S 6S", 805);
  chkeval("5C 6C 7C 9C 8C", 909);
  chkeval("TC JC QC KC AC", 1000);
}

void
eu054(char *ans) {
  FILE *fp = fopen("poker.txt", "r");
  if (!fp) {
    perror("poker.txt");
    exit(1);
  }
  char buf[4096];

  int p1wincount = 0;

  poktest();

  for (int hand = 0; hand < 1000; hand++) {
    char *line = fgets(buf, sizeof(buf), fp);
    if (line == 0) {
      fprintf(stderr, "Unexpected EOF on hand %d\n", hand);
      exit(1);
    }

    struct hand p1, p2;
    readhands(&p1, &p2, buf);

    int s1 = evalhand(&p1);
    int s2 = evalhand(&p2);

    if (s1 > s2) {
      p1wincount++;
    }
  }
  fclose(fp);

  sprintf(ans, "%d", p1wincount);
}
