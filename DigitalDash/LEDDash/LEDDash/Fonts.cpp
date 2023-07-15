#include <Arduino.h>
#include "Globals.h"

uint8_t heavyNumbersWidth[10] = {6,4,6,6,7,6,6,6,6,6};

uint8_t heavyNumbers[10][10][7] = {
  {//'0'
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00}
  },
  {//'1'
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00}
  },
  {//'2'
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00}
  },
  {//'3'
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00}
  },
  {//'4'
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00}
  },
  {//'5'
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00}
  },
  {//'6'
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00}
  },
  {//'7'
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00}
  },
  {//'8'
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00}
  },
  {//'9'
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00},
  {0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00}
  },
};
